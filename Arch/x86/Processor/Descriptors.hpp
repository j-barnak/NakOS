#pragma once

#include "Lib/Array.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>

namespace Processor {

struct [[gnu::packed]] DescriptorPointer
{
    std::uint16_t limit;
    void *base;
};

template<std::uint8_t Size>
class Descriptors
{
  public:
    // Forward Declaration
    struct Entry;

    Descriptors();
    void load_descriptor_entry(const Entry &entry, std::ptrdiff_t index);
    void load_gtdr();

    // clang-format off
    #pragma pack(push, 1)
    struct Entry
    {
        std::uint16_t segment_limit_low;
        std::uint16_t base_address_low;
        std::uint8_t base_address_mid;
        std::uint8_t type : 4;
        std::uint8_t system : 1;
        std::uint8_t descriptor_privilege_level : 1;
        std::uint8_t present : 1;
        std::uint8_t segment_limit_high : 4;
        std::uint8_t available : 1;
        std::uint8_t d_or_b : 1;
        std::uint8_t granularity : 1;
        std::uint8_t base_address_high;
    };
    // clang-format on
#pragma pack(pop)

  private:
    Descriptors<Size>::Entry m_entries[Size];
};

template<std::uint8_t Size>
Descriptors<Size>::Descriptors()
{}

template<std::uint8_t Size>
void Descriptors<Size>::load_gtdr()
{
    auto gdtr = DescriptorPointer { .limit = Size, .base = &m_entries };
    asm volatile(
        "cli;"
        "lgdtl %0;" ::"m"(gdtr));
}

template<std::uint8_t Size>
void Descriptors<Size>::load_descriptor_entry(const Descriptors<Size>::Entry &entry, std::ptrdiff_t index)
{
    [[unlikely]] if (index >= Size) {
        return;
    }
    m_entries[index] = entry;
}

}// namespace Processor
