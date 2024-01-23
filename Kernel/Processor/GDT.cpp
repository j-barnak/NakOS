#include "Processor/GDT.hpp"

Processor::GDT::GDT(const Processor::GDTR &gdtr) : m_gdtr { gdtr }
{
    load_gtdr();
}

void Processor::GDT::load_gtdr()
{
    asm volatile("lgdtl %0" ::"m"(m_gdtr));
}
