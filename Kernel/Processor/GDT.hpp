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
    void load_gtdr();
    void load_descriptor_entry(const Descriptor &Descriptor, std::ptrdiff_t index);

  private:
    GDTR m_gdtr;

    Lib::Array<Processor::Descriptor, 8> m_gdt;
    std::size_t m_size;
};

}// namespace Processor
