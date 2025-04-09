#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


// Sign-extends a bitfield with given size
int bitExtender(unsigned int field, unsigned int size) {
  unsigned int signo = (field >> (size - 1)) & 1;

  if (signo) {
    return (int)(field | (~((1 << size) - 1)));
  } else {
    return (int)field;
  }
}


/* Distances in BYTES */
int get_branch_distance(Instruction instruction) {
  // Para tipo B (branch), los bits inmediatos están distribuidos de forma irregular:
  // imm[12] | imm[10:5] | rs2 | rs1 | funct3 | imm[4:1] | imm[11] | opcode
  // Se reconstruye el offset según el formato RISC-V

  unsigned int imm = instruction.imm;

  // Extraer bits según el formato B
  unsigned int imm_12   = (imm >> 12) & 0x1;
  unsigned int imm_10_5 = (imm >> 5) & 0x3F;
  unsigned int imm_4_1  = (imm >> 1) & 0xF;
  unsigned int imm_11   = (imm >> 11) & 0x1;

  // Reconstruir el offset (en bits)
  unsigned int offset = (imm_12 << 12) |
                        (imm_11 << 11) |
                        (imm_10_5 << 5) |
                        (imm_4_1 << 1);

  return bitExtender(offset, 13); // Branch offset usa 13 bits (sign-extendido)
}


int get_jump_distance(Instruction instruction) {
  // Para tipo J (jal), los bits inmediatos están distribuidos así:
  // imm[20] | imm[10:1] | imm[11] | imm[19:12] | rd | opcode

  unsigned int imm = instruction.imm;

  unsigned int imm_20    = (imm >> 20) & 0x1;
  unsigned int imm_10_1  = (imm >> 1) & 0x3FF;
  unsigned int imm_11    = (imm >> 11) & 0x1;
  unsigned int imm_19_12 = (imm >> 12) & 0xFF;

  // Reconstruir el offset (en bits)
  unsigned int offset = (imm_20 << 20) |
                        (imm_19_12 << 12) |
                        (imm_11 << 11) |
                        (imm_10_1 << 1);

  return bitExtender(offset, 21); // Jump offset usa 21 bits (sign-extendido)
}


/* Offset in BYTES */
/* Used both in load and store */
int get_memory_offset(Instruction instruction) {
  int opcode = instruction.opcode;

  if (opcode == 0b0000011) {  // LOAD
    int offset = instruction.imm & 0xFFF;
    return bitExtender(offset, 12);

  } else if (opcode == 0b0100011) {  // STORE
    unsigned int imm_11_5 = (instruction.imm >> 5) & 0x7F;
    unsigned int imm_4_0 = instruction.imm & 0x1F;

    int offset = (imm_11_5 << 5) | imm_4_0;
    return bitExtender(offset, 12);
  }

  return 0;
}


void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}


void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}


void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}
