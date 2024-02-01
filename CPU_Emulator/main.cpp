#include "CPU.hpp"

int main()
{
    CPU cpu;
    Mem mem;
    Mem* ptr = &mem;
    cpu.reset(mem);

    // inline start
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;

    // inline end
    cpu.Execute(9, mem);
    return 0;
}
