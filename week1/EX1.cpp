#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
unsigned char LEDs;

int LED_function(int input) {
	LEDs = (1 << input); //input만큼 1을 왼쪽으로 shift
	return LEDs;
}

int main() {
	int num;

	scanf("%d", &num);

	int return_value = LED_function(num);
	printf("return_value: %d\n", return_value);

	return 0;
}