#include "Processor/GDT.hpp"
#include "Descriptor.hpp"

Processor::GDT::GDT(const Processor::GDTR &gdtr) : m_gdtr { gdtr }, m_size { 0 }
{
    load_gtdr();
    m_descriptor_entries = static_cast<Descriptor *>(m_gdtr.base);
}

void Processor::GDT::load_gtdr()
{
    asm volatile(
        "cli;"
        "lgdtl %0;"
        "sti;" ::"m"(m_gdtr));
}

void Processor::GDT::push_descriptor_entry(const Descriptor &descriptor)
{
    m_descriptor_entries[m_size] = descriptor;
}
