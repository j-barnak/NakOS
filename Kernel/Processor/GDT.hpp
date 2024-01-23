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
    GDT(const GDTR &gdtr);
    void load_gtdr();

  private:
    GDTR m_gdtr;
};

}// namespace Processor
