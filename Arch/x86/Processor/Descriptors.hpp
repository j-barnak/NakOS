#pragma once

#include <cstdint>
#include <memory>

inline void crash()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wundef"
    int *__CRASH_PTR = nullptr;
    *__CRASH_PTR;
#pragma GCC diagnostic pop
}


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

    static void set_base(const std::uint32_t base, Descriptors<Size>::Entry &descriptor);
    static void set_flags(const std::uint8_t flags, Descriptors<Size>::Entry &descriptor);
    static void set_access_byte(const std::uint8_t access_byte, Descriptors<Size>::Entry &descriptor);

    // clang-format off
    constexpr std::uint8_t amount_of_entries() const { return Size; }
    // clang-format on

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
        std::uint8_t db : 1;
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

template<std::uint8_t Size>
void Descriptors<Size>::set_base(const std::uint32_t base, Descriptors<Size>::Entry &entry)
{
    const std::uint32_t lower_mask = 0x0000FFFF;

    const std::uint32_t middle_mask = 0x00FF0000;
    const std::uint8_t middle_shift = 16;

    const std::uint32_t high_mask = 0xFF000000;
    const std::uint8_t high_shift = 24;

    entry.base_address_low = (lower_mask & base);
    entry.base_address_mid = (middle_mask & base) >> middle_shift;
    entry.base_address_high = (high_mask & base) >> high_shift;
}

// Flags:
//     +---+---+---+---+
//     | 1 | 1 | 1 | 1 |
//     +---+---+---+---+
//     | G | DB| L | R |
//     +---+---+---+---+
template<std::uint8_t Size>
void Descriptors<Size>::set_flags(std::uint8_t flags, Descriptors<Size>::Entry &entry)
{
    [[unlikely]] if (flags > 0b1111) {
        crash();
    }

    const std::uint8_t g_mask = 0b1000;
    const std::uint8_t g_shift = 3;

    const std::uint8_t db_mask = 0b0100;
    const std::uint8_t db_shift = 2;

    const std::uint8_t l_mask = 0b0010;
    const std::uint8_t l_shift = 1;

    const std::uint8_t r_mask = 0b0000;
    const std::uint8_t r_shift = 0;

    entry.granularity = (g_mask & flags) > g_shift;
    entry.db = (db_mask & flags) > db_shift;
    entry.l_mask = (l_mask & flags) > db_shift;
    entry.reserved = r_mask & flags;
}

// Access Byte:
//     +---+----+---+---+---+---+---+
//     | 1 | 02 | 1 | 1 | 1 | 1 | 1 |
//     +---+----+---+---+---+---+---+
//     | P | DPL| S | E | DC| RW| A |
//     +---+----+---+---+---+---+---+
template<std::uint8_t Size>
void Descriptors<Size>::set_access_byte(std::uint8_t access_byte, Descriptors<Size>::Entry &entry)
{}

} // namespace Processor
