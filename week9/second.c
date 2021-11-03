#include <avr/io.h>
#include <util/delay.h>
void main()
{
	unsigned char value = 128;
	DDRA = 0xff;
	for (;;)
	{
		for(int i=0;i<7;i++){
			PORTA = value;
			_delay_ms(2000);
			value >>= 1;
		}
		for(int i=0;i<7;i++){
			PORTA = value;
			_delay_ms(2000);
			value <<= 1;
		}
	}
}
