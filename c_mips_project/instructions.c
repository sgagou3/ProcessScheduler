#include <stdint.h>
#include <stdlib.h>

#include "bit_utils.h"
#include "instructions.h"

instruction_type get_type_of_instruction(uint32_t instruct) {
	uint32_t instruct_value = 0;
	int8_t counter = OPCODE_START_BIT;
	int idx = OPCODE_START_BIT - OPCODE_END_BIT;
	while (counter >= OPCODE_END_BIT) {
		if (instruct & (1 << counter)) {
			instruct_value += (1 << idx);
		}
		counter--;
	}
	if (instruct_value == 0) {
		return R_TYPE;
	}
	else {
		return I_TYPE;
	}
} 

r_instruction* create_r_instruction(uint32_t instruct) {
	r_instruction* ri = (r_instruction*)malloc(sizeof(r_instruction));
	int8_t format_value = 0;
	int8_t counter = RS_START_BIT;
	int8_t idx = RS_START_BIT - RS_END_BIT;
	while (counter >= RS_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	counter = RT_START_BIT;
	ri->rs = format_value;
	format_value = 0;
	idx = RT_START_BIT - RT_END_BIT;
	while (counter >= RT_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	counter = RD_START_BIT;
	ri->rt = format_value;
	format_value = 0;
	idx = RD_START_BIT - RD_END_BIT;
	while (counter >= RD_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	counter = SHAMT_START_BIT;
	ri->rd = format_value;
	format_value = 0;
	idx = SHAMT_START_BIT - SHAMT_END_BIT;
	while (counter >= SHAMT_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	counter = FUNC_START_BIT;
	ri->shamt = format_value;
	format_value = 0;
	idx = FUNC_START_BIT - FUNC_END_BIT;
	while (counter >= FUNC_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	ri->func = format_value;
	return ri;
} 

i_instruction* create_i_instruction(uint32_t instruct) {
	i_instruction* ii = (i_instruction*)malloc(sizeof(i_instruction));
	int8_t counter = OPCODE_START_BIT;
	uint8_t format_value = 0;
	int8_t idx = OPCODE_START_BIT - OPCODE_END_BIT;
	while (counter >= OPCODE_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	ii->opcode = format_value;
	counter = RS_START_BIT;
	format_value = 0;
	idx = RS_START_BIT - RS_END_BIT;
	while (counter >= RS_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	counter = RT_START_BIT;
	ii->rs = format_value;
	format_value = 0;
	idx = RT_START_BIT - RT_END_BIT;
	while (counter >= RT_END_BIT) {
		if (instruct & (1 << counter)) {
			format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	ii->rt = format_value;
	counter = IMMEDIATE_START_BIT;
	uint16_t expanded_format_value = 0;
	idx = IMMEDIATE_START_BIT - IMMEDIATE_END_BIT;
	while (counter >= IMMEDIATE_END_BIT) {
		if (instruct & (1 << counter)) {
			expanded_format_value += (1 << idx);
		}
		counter--;
		idx--;
	}
	ii->immediate = expanded_format_value;
	return ii;
} 


