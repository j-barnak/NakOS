#include "CPU/CPU.hpp"

void CPU::load_gtdr(GDTR gdt_register = { .base = 0, .limit = 0 })
{
    asm volatile("lgdtl %0" ::"m"(gdt_register));
}
