#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
unsigned char LEDs;

void LED_function( ) {
	LEDs = 1;
	printf("%d ", LEDs);

	//LEDs ���� 10000000�� �� ������ �������� shift
	while (LEDs != (0x80)) {
		LEDs = LEDs << 1;
		printf("%d ", LEDs);
	}

	//LEDs ���� 00000001�� �� ������ ���������� shift
	while (LEDs != (0x01)) {
		LEDs = LEDs >> 1;
		printf("%d ", LEDs);
	}
	printf("\n");
}

int main() {
	//4�� �ݺ�
	for (int i = 0; i < 4; i++) {
		LED_function();
	}

	return 0;
}