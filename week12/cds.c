#define F_CPU 16000000UL
#include <avr/io.h>
#define CDS_VALUE 871
#include <avr/interrupt.h>
#include <util/delay.h>

#define START 1
#define STOP 0

void init_adc();
unsigned short read_adc();
void show_adc(unsigned short value);

const unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f };
const unsigned char fnd_sel[4] = { 0x08, 0x04, 0x02, 0x01 };
const unsigned char dot = 0x80;
int count = 0;
unsigned char num[4];
int signal;

ISR(INT4_vect){
	if(signal == START){

		signal = STOP;
	}
	else{
		signal = START;
	}
	_delay_ms(10);
}

ISR(INT5_vect){
	if(signal == STOP){
		count = 0;
		_delay_ms(10);	
	}
}

void display_fnd(int c){
	int i;
	num[0] = digit[(count/1000)];
	num[1] = digit[(count/100)%10]+dot;
	num[2] = digit[(count/10)%10];
	num[3] = digit[count%10];

	for(i=0;i<4;i++){
		PORTC = num[i];
		PORTG = fnd_sel[i];
		_delay_us(2500);
	}
}

int main(){
	DDRC = 0xff;
	DDRG = 0x0f;
	DDRE = 0xcf;
	SREG |= 1 << 7;
	EIMSK = 0x30;
	EICRB = 0x0a;
	signal = 0;

	unsigned short value;

	DDRA=0xff;

	init_adc();
	while(1){
		value=read_adc();
		show_adc(value);
	}
}

void init_adc(){
	ADMUX=0x00;
		// 00000000
		// REFS(1:0) = "00" AREF(+5V) 기준전압 사용
		// ADLAR = '0' 디폴트 오른쪽 정렬
		// MUX(4:0) = "00000" ADC0 사용, 단극 입력
	ADCSRA = 0x87;
		// 10000111
		// ADEN = '1' ADC를 Enable
		// ADFR = '0' single conversion 모드
		// ADPS(2:0) = "111" 프리스케일러 128분주
}

unsigned short read_adc(){
	unsigned char adc_low,adc_high;
	unsigned short value;
	ADCSRA |= 0x40; // ADC start conversion, ADSC = '1'
	while((ADCSRA & (0x10)) != 0x10); // ADC 변환 완료 검사
	adc_low=ADCL;
	adc_high=ADCH;
	value = (adc_high <<8) | adc_low;
	
	return value;
}

void show_adc(unsigned short value){
	if(value < CDS_VALUE) {
		PORTA=0xff;
		if(signal==START){
			display_fnd(count);
			count = (count+1)%10000;
		}else if(signal==STOP){
			display_fnd(0);
		}
	}
	else {
		PORTA=0x00;
		for(int i=0;i<4;i++){
			PORTC = 0x00;
			PORTG = fnd_sel[i];
			_delay_us(2500);
		}
	}
}
