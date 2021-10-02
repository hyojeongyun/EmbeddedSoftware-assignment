#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
unsigned char LEDs;

void LED_function( ) {
	LEDs = 1;
	printf("%d ", LEDs);

	//LEDs 값이 10000000이 될 때까지 왼쪽으로 shift
	while (LEDs != (0x80)) {
		LEDs = LEDs << 1;
		printf("%d ", LEDs);
	}

	//LEDs 값이 00000001이 될 때까지 오른쪽으로 shift
	while (LEDs != (0x01)) {
		LEDs = LEDs >> 1;
		printf("%d ", LEDs);
	}
	printf("\n");
}

int main() {
	//4번 반복
	for (int i = 0; i < 4; i++) {
		LED_function();
	}

	return 0;
}