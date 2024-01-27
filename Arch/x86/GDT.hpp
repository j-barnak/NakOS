#pragma once

#include "Array.hpp"
#include "Lib/Array.hpp"
#include "Processor/Descriptor.hpp"
#include <cstddef>
#include <cstdint>

namespace Processor {

// TODO: The base and limit are messed up. Switch them
struct [[gnu::packed]] GDTR
{
    std::uint16_t limit;
    void *base;
};

template<std::uint8_t Size>
class GDT
{
  public:
    GDT(const GDTR &gdtr);
    void load_descriptor_entry(const Descriptor &Descriptor, std::ptrdiff_t index);

  private:
    GDTR m_gdtr;
    Lib::Array<Processor::Descriptor, Size> m_gdt;

    void load_gtdr();
};

template<std::uint8_t Size>
Processor::GDT<Size>::GDT(const Processor::GDTR &gdtr) : m_gdtr { gdtr }
{
    m_gdtr.base = this;
    m_gdtr.limit = static_cast<std::uint16_t>(sizeof(m_gdt));
    load_gtdr();
}

template<std::uint8_t Size>
void Processor::GDT<Size>::load_gtdr()
{
    asm volatile(
        "cli;"
        "lgdtl %0;" ::"m"(m_gdtr));
}

template<std::uint8_t Size>
void Processor::GDT<Size>::load_descriptor_entry(const Processor::Descriptor &descriptor, std::ptrdiff_t index)
{
    m_gdt[index] = descriptor;
}

}// namespace Processor
