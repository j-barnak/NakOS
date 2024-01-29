#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"

auto gdt = Processor::Descriptors<8> {};

void gdt_init()
{
    gdt.load_gtdr();
    int a = 1;
}
