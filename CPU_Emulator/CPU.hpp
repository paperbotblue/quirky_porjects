#pragma once

#include <stdio.h>
#include <stdlib.h>

//

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte DATA[MAX_MEM];

    void Initialise();

    //reading 1 byte
    Byte operator[](u32 Address) const;

    //Writing 1 byte
    Byte& operator[](u32 Address);

    void WriteWord(u32& Cycles, Word Value, u32 Address);
};

struct CPU
{

    Word PC; // 16 bit program counter 
    Word SP; // 16 bit stack pointer

    Byte A, X, Y; // 8 bit register

    Byte C = 1; // Carry flag
    Byte Z = 1; // Zero flag
    Byte I = 1; // Interrupt enable/disable flag
    Byte D = 1; // Decimal flag
    Byte B = 1; // Break command
    Byte V = 1; // Overflow flag
    Byte N = 1; // Negative flag

    void reset(Mem& mem);

    Byte FetchByte(u32& Cycles, Mem& memory);

    Word FetchWord(u32& Cycles, Mem& memory);



    Byte ReadByte(u32& Cycles, Byte Address, Mem& memory);


    // Opcodes
    static constexpr Byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5,
        INS_LDA_ZPX = 0xB5,
        INS_JSR = 0x20;

    void LDASetStatus();

    void Execute(u32 Cycles, Mem& mem);
};


void Mem::Initialise()
{
    for (u32 i = 0; i < MAX_MEM; i++)
    {
        DATA[i] = 0;
    }
}

Byte Mem::operator[](u32 Address) const
{
    return DATA[Address];
}

Byte& Mem::operator[](u32 Address)
{
    return DATA[Address];
}

void Mem::WriteWord(u32& Cycles, Word Value, u32 Address)
{
    DATA[Address] = Value & 0xFF;
    DATA[Address + 1] = (Value >> 8);
    Cycles -= 2;
}

void CPU::reset(Mem& mem)
{
    PC = 0xFFFC;
    SP = 0x0100;
    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;

    mem.Initialise();
}


Byte CPU::FetchByte(u32& Cycles, Mem& memory)
{
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
}

Word CPU::FetchWord(u32& Cycles, Mem& memory)
{
    Word Data = memory[PC];
    PC++;

    Data |= (memory[PC] << 8);
    PC++;
    Cycles -= 2;

    return Data;
}

Byte CPU::ReadByte(u32& Cycles, Byte Address, Mem& memory)
{
    Byte Data = memory[Address];
    Cycles--;
    return Data;
}

void CPU::LDASetStatus()
{
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::Execute(u32 Cycles, Mem& mem)
{
    while (Cycles > 0)
    {
        Byte Instruction = FetchByte(Cycles, mem);
        switch (Instruction)
        {
        case INS_LDA_IM:
        {
            Byte value = FetchByte(Cycles, mem);
            A = value;
            LDASetStatus();
        }break;
        case INS_LDA_ZP:
        {
            Byte ZeroPageAddress = FetchByte(Cycles, mem);
            A = ReadByte(Cycles, ZeroPageAddress, mem);
            LDASetStatus();
        }break;
        case INS_LDA_ZPX:
        {
            Byte ZeroPageAddress = FetchByte(Cycles, mem);
            ZeroPageAddress += X;
            Cycles--;
            A = ReadByte(Cycles, ZeroPageAddress, mem);
            LDASetStatus();
        }break;
        case INS_JSR:
        {
            Word SubAddress = FetchWord(Cycles, mem);
            mem.WriteWord(Cycles, PC - 1, SP);
            PC = SubAddress;
            Cycles--;
        }break;
        default:
        {
            printf("Instruction not handled instruction :%d, Cycle: %d", Instruction, Cycles);
        }break;
        }

    }
}
