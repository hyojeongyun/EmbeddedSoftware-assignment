#include <avr/io.h>
#include <util/delay.h>

unsigned char digit[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f };
unsigned char dot = 0x80;
unsigned char fnd_sel[4] = {0x08, 0x04, 0x02, 0x01 };

int printNum(unsigned char arr[4]){
	int idx;
	for(idx = 0; idx<4; idx++){
		PORTG = fnd_sel[idx];
		PORTC = arr[idx];
		_delay_us(2500);
	}
}


int main() {
	int i, j, k, l;
	unsigned char num[4];

	DDRC = 0xff;
	DDRG = 0x0f;

	for(i=0;; i++){
		if(i==10)
			i = 0;
		num[0] = digit[i];
		for(j=0; j<10; j++){
			num[1] = digit[j] + dot;
			for(k=0; k<10; k++){
				num[2] = digit[k];
				for(l=0; l<10; l++){
					num[3] = digit[l];
					printNum(num);
				}
			}
		}
	}
}
