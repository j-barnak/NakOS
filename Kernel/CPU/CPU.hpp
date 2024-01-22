#pragma once

#include <cstdint>

#pragma pack(push, 1)
struct GDTR
{
    std::uint16_t base;
    std::uint32_t limit;
};

#pragma pack(pop)

#pragma pack(push, 1)
class CPU
{
  public:
    static void load_gtdr(GDTR gdt_register);

  private:
};
#pragma pack(pop)
