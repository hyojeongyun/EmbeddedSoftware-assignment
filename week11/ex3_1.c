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

const int scale[8] = { DO, RE, MI, FA, SOL, LA, TI, UDO };
int state = ON;
int index = 0;
int flag = 0;

ISR(TIMER0_OVF_vect) {
	if (state == ON) {
		PORTB = 0x00;
		state = OFF;
	}
	else {
		PORTB = 0x10;
		state = ON;
	}
	TCNT0 = scale[index];
	flag = 1;
}

ISR(INT5_vect) {
	if (flag == 1) {
		index = (index + 1) % 8;
		flag = 0;
		_delay_ms(100);
	}
}

int main() {
	DDRB = 0x10;
	DDRE = 0xDF;
	EICRB = 0x08;
	EIMSK = 0x20;
	sei();
	TCCR0 = 0x03;
	TIMSK = 0x01;


	for (;;) {
	}
}
