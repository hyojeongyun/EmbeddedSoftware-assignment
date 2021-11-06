#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define START 1
#define STOP 0

const unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f };
const unsigned char fnd_sel[4] = { 0x08, 0x04, 0x02, 0x01 };
const unsigned char dot = 0x80;
int count =0;
unsigned char num[4];
int signal;

ISR(INT4_vect){
	if(signal == START)
		signal = STOP;
	else
		signal = START;

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

	for(;;){
		display_fnd(count);
		if(signal==START)
			count = (count+1)%10000;
	}
}
