#include "bit_utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char* itob(int num, int size) {
	char* result = (char*)malloc(sizeof(char) * size);
	int idx = size - 1;
	while (idx >= 0) {
		if (num & 1) {
			result[idx] = '1';
		}
		else {
			result[idx] = '0';
		}
		idx--;
		num >>= 1;
	}
	result[size] = '\0';
	return result;
}

int mask_bits(int num, int mask) {
	return num & mask;
}

int set_bits(int num, int bits) {
	return num | bits;
}

int inverse_bits(int num, int bits) {
	return num ^ bits;
}

int bit_select(int num, int startbit, int endbit) {
	int idx = 31;
	int total = 0;
	int bit_idx = startbit - endbit;
	while (idx >= 0) {
		if (idx <= startbit && idx >= endbit) {
			if (num & (1 << MSB_INDEX)) {
				total += (1 << (bit_idx));
			}
			bit_idx--;
		}
		idx--;
		num <<= 1;
	}
	return total;
}