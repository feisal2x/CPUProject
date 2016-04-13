#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdint.h>

#define BUFFER_SIZE  0x4000
#define REF_SIZE     0x10
#define MAX	0xF

#define TMP_SP   0xD
#define TMP_LR   0xE
#define TMP_PC   0xF
#define SP      reg[TMP_SP]
#define LR      reg[TMP_LR]
#define PC      reg[TMP_PC]
#define LINE_LENGTH     0x10


int LoadFile();
void WriteFile();
void MemDump();
void MemModify();
void RegistryDisplay();
void ZeroRegistry();
void Trace();
void Fetch();
void InstructionSet();
void RunProgram();

static uint32_t  reg[REF_SIZE];

static uint32_t  R0;
static uint32_t  R1;
static uint32_t  R2;
static uint32_t  R3;
static uint32_t  R4;
static uint32_t  R5;
static uint32_t  R6;
static uint32_t  R7;
static uint32_t  R8;
static uint32_t  R9;
static uint32_t  R10;
static uint32_t  R11;
static uint32_t  R12;


static uint32_t  MAR;
static uint32_t  MBR;
static uint32_t  IR;
static uint32_t  ALU;
static uint16_t  CIR;
static uint16_t  IR0;
static uint16_t  IR1;



/* Flags */
static uint8_t flag_SIGN;
static uint8_t flag_ZERO;
static uint8_t flag_CARRY;
static uint8_t flag_STOP;
static uint8_t flag_IR; 


#endif
