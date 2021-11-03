#include <avr/io.h>
#include <util/delay.h>

void main()
{
	unsigned char value[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	DDRA = 0xff;

	for(;;)
	{
		PORTA = value[0];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[0];
		_delay_ms(4000);
		PORTA = value[4];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[4];
		_delay_ms(4000);
		PORTA = value[5];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[5];
		_delay_ms(4000);
		PORTA = value[4];
		_delay_ms(4000);
		PORTA = value[3];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[3];
		_delay_ms(4000);
		PORTA = value[2];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[2];
		_delay_ms(4000);
		PORTA = value[1];
		_delay_ms(2000);
		PORTA = 0;
		_delay_ms(2000);
		PORTA = value[1];
		_delay_ms(4000);
		PORTA = value[0];
		_delay_ms(4000);

	}
}
