#pragma once

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

class GDT
{
  public:
    GDT(const GDTR &gdtr);
    void load_gtdr();
    void push_descriptor_entry(const Descriptor &Descriptor);

  private:
    GDTR m_gdtr;
    Descriptor *m_descriptor_entries;
    std::size_t m_size;
};

}// namespace Processor
