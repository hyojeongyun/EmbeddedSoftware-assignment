#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
unsigned char LEDs;

int main() {
	scanf("%uc", &LEDs);

	int count = 0;
	int result = 0;

	for (int i = 0; i < 8; i++) {
		if (LEDs & 0x80) {
			count++;
		}
		LEDs = LEDs << 1;
	}

	for (int i = 0; i < count; i++) {
		result |= 0x80;
		result = result >> 1;
	}

	result = result << 1;

	printf("1�� ����? %d\n", count);
	printf("Shift ���� ����? %d", result);

	return 0;
}