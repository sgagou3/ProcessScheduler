#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "instructions.h"

#define REGISTER_SIZE 32

void execute_r_instruction(r_instruction* instruct);
void execute_i_instruction(i_instruction* instruct);

static uint16_t registers[REGISTER_SIZE] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

int main() {
	uint32_t instruct;
	while (true) {
		printf("Please enter your instruction as a 32-bit integer: ");
		if (scanf("%u", &instruct) != 1) {
			printf("\n");
			fprintf(stderr, "Failed to read instruction!\n");
			return EXIT_FAILURE;
		}

		if (instruct == UINT_MAX)
			return EXIT_SUCCESS;

		if (get_type_of_instruction(instruct) == R_TYPE) {
			r_instruction* r_instruct = create_r_instruction(instruct);
			execute_r_instruction(r_instruct);
			free(r_instruct);
		}
		else { 
			i_instruction* i_instruct = create_i_instruction(instruct);
			execute_i_instruction(i_instruct);
			free(i_instruct);
		}
		printf("%s", "Current register status:\n");
		printf("[");
		for (int i = 0; i < REGISTER_SIZE; i++) {
			printf("%d", registers[i]);
			if (i != REGISTER_SIZE - 1)
				printf(", ");
		}
		printf("]\n");
	}
}

void execute_r_instruction(r_instruction* instruct) {
	if (instruct->func == SLL_FUNC) {
		registers[instruct->rd] = registers[instruct->rt] << instruct->shamt;
	}
	else if (instruct->func == SRA_FUNC) {
		registers[instruct->rs] = (int32_t)registers[instruct->rs];
		registers[instruct->rd] = registers[instruct->rt] >> instruct->shamt;
	}
	else if (instruct->func == ADD_FUNC) {
		registers[instruct->rd] = registers[instruct->rs] + registers[instruct->rt];
	}
	else if (instruct->func == SUB_FUNC) {
		registers[instruct->rd] = registers[instruct->rs] - registers[instruct->rt];
	}
	else if (instruct->func == AND_FUNC) {
		registers[instruct->rd] = registers[instruct->rs] & registers[instruct->rt];
	}
	else if (instruct->func == OR_FUNC) {
		registers[instruct->rd] = registers[instruct->rs] | registers[instruct->rt];
	}
	else if (instruct->func == NOR_FUNC) {
		registers[instruct->rd] = ~(registers[instruct->rs] | registers[instruct->rt]);
	}
} 

void execute_i_instruction(i_instruction* instruct) {
	if (instruct->opcode == ADDI_OPCODE) {
		registers[instruct->rt] = registers[instruct->rs] + instruct->immediate;
	}
	else if (instruct->opcode == ANDI_OPCODE) {
		registers[instruct->rt] = registers[instruct->rs] & instruct->immediate;
	}
	else if (instruct->opcode == ORI_OPCODE) {
		registers[instruct->rt] = registers[instruct->rs] | instruct->immediate;
	}
}  
