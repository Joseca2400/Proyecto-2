#include <stdio.h> // para stderr
#include <stdlib.h> // para exit()
#include "types.h"
#include "utils.h"

// Declaraciones adelantadas
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_auipc(Instruction);
void write_lui(Instruction);
void write_jalr(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);

void decode_instruction(Instruction instruction) {
    uint32_t opcode = instruction.opcode;

    switch (opcode) {
        case 0x33: // R-type
            write_rtype(instruction);
            break;
        case 0x13: // I-type (except load)
            write_itype_except_load(instruction);
            break;
        case 0x03: // Load (I-type)
            write_load(instruction);
            break;
        case 0x23: // Store (S-type)
            write_store(instruction);
            break;
        case 0x63: // Branch (B-type)
            write_branch(instruction);
            break;
        case 0x17: // AUIPC (U-type)
            write_auipc(instruction);
            break;
        case 0x37: // LUI (U-type)
            write_lui(instruction);
            break;
        case 0x67: // JALR (I-type)
            write_jalr(instruction);
            break;
        case 0x6F: // JAL (J-type)
            write_jal(instruction);
            break;
        case 0x73: // ECALL/EBREAK (I-type)
            write_ecall(instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_rtype(Instruction instruction) {
    switch (instruction.rtype.funct3) {
        case 0x0:
            if (instruction.rtype.funct7 == 0x00) {
                print_rtype("add", instruction);
            } else if (instruction.rtype.funct7 == 0x20) {
                print_rtype("sub", instruction);
            } else {
                handle_invalid_instruction(instruction);
            }
            break;
        case 0x1:
            print_rtype("sll", instruction);
            break;
        case 0x2:
            print_rtype("slt", instruction);
            break;
        case 0x3:
            print_rtype("sltu", instruction);
            break;
        case 0x4:
            print_rtype("xor", instruction);
            break;
        case 0x5:
            if (instruction.rtype.funct7 == 0x00) {
                print_rtype("srl", instruction);
            } else if (instruction.rtype.funct7 == 0x20) {
                print_rtype("sra", instruction);
            } else {
                handle_invalid_instruction(instruction);
            }
            break;
        case 0x6:
            print_rtype("or", instruction);
            break;
        case 0x7:
            print_rtype("and", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_itype_except_load(Instruction instruction) {
    int imm = bitExtender(instruction.itype.imm, 12);
    switch (instruction.itype.funct3) {
        case 0x0:
            print_itype_except_load("addi", instruction, imm);
            break;
        case 0x2:
            print_itype_except_load("slti", instruction, imm);
            break;
        case 0x3:
            print_itype_except_load("sltiu", instruction, imm);
            break;
        case 0x4:
            print_itype_except_load("xori", instruction, imm);
            break;
        case 0x6:
            print_itype_except_load("ori", instruction, imm);
            break;
        case 0x7:
            print_itype_except_load("andi", instruction, imm);
            break;
        case 0x1:
            print_itype_except_load("slli", instruction, imm);
            break;
        case 0x5:
            if ((instruction.itype.imm & 0xFE0) == 0x00) {
                print_itype_except_load("srli", instruction, imm);
            } else if ((instruction.itype.imm & 0xFE0) == 0x400) {
                print_itype_except_load("srai", instruction, imm);
            } else {
                handle_invalid_instruction(instruction);
            }
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
        case 0x0:
            print_load("lb", instruction);
            break;
        case 0x1:
            print_load("lh", instruction);
            break;
        case 0x2:
            print_load("lw", instruction);
            break;
        case 0x4:
            print_load("lbu", instruction);
            break;
        case 0x5:
            print_load("lhu", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_store(Instruction instruction) {
    switch (instruction.stype.funct3) {
        case 0x0:
            print_store("sb", instruction);
            break;
        case 0x1:
            print_store("sh", instruction);
            break;
        case 0x2:
            print_store("sw", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_branch(Instruction instruction) {
    switch (instruction.btype.funct3) {
        case 0x0:
            print_branch("beq", instruction);
            break;
        case 0x1:
            print_branch("bne", instruction);
            break;
        case 0x4:
            print_branch("blt", instruction);
            break;
        case 0x5:
            print_branch("bge", instruction);
            break;
        case 0x6:
            print_branch("bltu", instruction);
            break;
        case 0x7:
            print_branch("bgeu", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_auipc(Instruction instruction) {
    int imm = instruction.utype.imm <<
::contentReference[oaicite:0]{index=0}
 
