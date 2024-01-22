#pragma once

#include <cstdint>

class [[gnu::packed]] Descriptor
{
  public:
    std::uint8_t get_granularity() const;

  private:
    std::uint32_t m_descriptor_with_permissions = 0x0;
    std::uint32_t m_descriptor_with_base_limit = 0x0;
};
