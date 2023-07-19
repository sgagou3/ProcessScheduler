#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

#define OPCODE_START_BIT 31
#define OPCODE_END_BIT 26
#define RS_START_BIT 25
#define RS_END_BIT 21
#define RT_START_BIT 20
#define RT_END_BIT 16
#define RD_START_BIT 15
#define RD_END_BIT 11
#define SHAMT_START_BIT 10
#define SHAMT_END_BIT 6
#define FUNC_START_BIT 5
#define FUNC_END_BIT 0
#define IMMEDIATE_START_BIT 15
#define IMMEDIATE_END_BIT 0

#define R_TYPE_OPCODE 0b000000
#define ADDI_OPCODE 0b001000
#define ANDI_OPCODE 0b001100
#define ORI_OPCODE 0b001101

#define SLL_FUNC 0b000000
#define SRA_FUNC 0b000011
#define ADD_FUNC 0b100000
#define SUB_FUNC 0b100010
#define AND_FUNC 0b100100
#define OR_FUNC 0b100101
#define NOR_FUNC 0b100111

typedef struct {
	uint8_t rs;
	uint8_t rt;
	uint8_t rd;
	uint8_t shamt;
	uint8_t func;
} r_instruction;

typedef struct {
	uint8_t opcode;
	uint8_t rs;
	uint8_t rt;
	uint16_t immediate;
} i_instruction;

typedef enum {
	R_TYPE,
	I_TYPE
} instruction_type;

instruction_type get_type_of_instruction(uint32_t instruct);

r_instruction* create_r_instruction(uint32_t instruct);

i_instruction* create_i_instruction(uint32_t instruct);

#endif 
