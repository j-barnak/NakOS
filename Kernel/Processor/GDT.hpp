#pragma once

#include <cstdint>

namespace Processor {

struct [[gnu::packed]] GDTR
{
    std::uint16_t base;
    std::uint32_t limit;
};

class GDT
{
  public:
    void load_gtdr(GDTR gdt_register);

  private:
    GDTR m_gdtr;
};

}// namespace Processor
