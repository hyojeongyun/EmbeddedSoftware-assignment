#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f };
unsigned char fnd_sel[4] = { 0x01, 0x02, 0x04, 0x08 };

int main() {
	int r;
	int i, j;

	DDRA = 0xff;
	DDRC = 0xff;
	DDRG = 0x0f;

	for (;;) {
		r = rand()%8;
		PORTA = 1 << r;
		for (i=0; i<500; i++) {
			for (j = 0; j < 4; j++) {
				PORTC = digit[r];
				PORTG = fnd_sel[j];
				_delay_ms(2);
			}
		}
	}
}
