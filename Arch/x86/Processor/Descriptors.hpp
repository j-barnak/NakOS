#pragma once

#include <cstdint>
#include <memory>

namespace Processor {

template<std::uint8_t Size>
class Descriptors
{
  public:
    // Forward Declarations
    struct [[gnu::packed]] Entry;
    struct [[gnu::packed]] Pointer;

    Descriptors() = default;

    void load_descriptor_entry(const Entry &entry, std::ptrdiff_t index);
    void load_gdtr();
    // clang-format off
    constexpr std::uint8_t amount_of_entries() const { return Size; }
    
    struct [[gnu::packed]] Entry
    {
        std::uint16_t segment_limit_low;
        std::uint16_t base_address_low;
        std::uint8_t base_address_mid;
        std::uint8_t type : 4;
        std::uint8_t system : 1;
        std::uint8_t descriptor_privilege_level : 2;
        std::uint8_t present : 1;
        std::uint8_t segment_limit_high : 4;
        std::uint8_t available : 1;
        std::uint8_t reserved : 1;
        std::uint8_t d_or_b : 1;
        std::uint8_t granularity : 1;
        std::uint8_t base_address_high;
    };
    // clang-format on

    struct [[gnu::packed]] Pointer
    {
        std::uint16_t limit;
        void *base;
    };

  private:
    Descriptors<Size>::Entry m_entries[Size];
};

template<std::uint8_t Size>
void Descriptors<Size>::load_gdtr()
{
    auto gdtr = Descriptors<Size>::Pointer { .limit = Size, .base = &m_entries };

    asm volatile(
        "cli;"
        "lgdt %0;" ::"m"(gdtr));
}

template<std::uint8_t Size>
void Descriptors<Size>::load_descriptor_entry(const Descriptors<Size>::Entry &entry, std::ptrdiff_t index)
{
    [[unlikely]] if (index >= Size || index < 0) {
        return;
    }

    m_entries[index] = entry;
}

}// namespace Processor
