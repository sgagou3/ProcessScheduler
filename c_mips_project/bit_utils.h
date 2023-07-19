#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define SIZE sizeof(int) * 8
#define MSB_INDEX 31

char* itob(int num, int size);

int mask_bits(int num, int mask);

int set_bits(int num, int bits);

int inverse_bits(int num, int bits);

int bit_select(int num, int startbit, int endbit);

#endif
