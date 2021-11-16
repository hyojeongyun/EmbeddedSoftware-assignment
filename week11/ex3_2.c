#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

#define DO 17
#define RE 43
#define MI 66
#define FA 77
#define SOL 97
#define LA 114
#define TI 117
#define UDO 137

#define ON 1
#define OFF 0

const unsigned char melody[20]={DO, 0, DO, SOL,0, SOL, LA,0, LA, SOL, FA,0, FA, MI,0, MI, RE,0, RE, DO};
int interval[20]={5000,50, 5000, 5000,50, 5000, 5000,50, 5000, 5000, 5000,50, 5000, 5000,50,5000, 5000,50, 5000, 5000};

volatile int index=0;
volatile int state=OFF;

ISR(TIMER0_OVF_vect){
	if(state==ON){
	PORTB=0x00;
	state=OFF;
	}
	else{
	PORTB=0x10;
	state=ON;
	}
	TCNT0=melody[index];
}


int main(){
	DDRB=0x10;
	TCCR0=0x03;
	TIMSK=0x01;
	sei();
	index = 0;

	TCNT0=melody[index];

	while(index!=20){
		
		_delay_ms(interval[index]);

		index=index+1;
	}
}
