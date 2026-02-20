#pragma once

#include <Lib/Error.hpp>
#include <cstdint>
#include <memory>

namespace Processor {

enum class AccessByte : std::uint8_t {
    // Data Segments
    DataReadOnly = 0b0000,
    DataReadOnlyAccessed = 0b0001,
    DataReadWrite = 0b0010,
    DataReadWriteAccessed = 0b0011,
    DataReadOnlyExpandDown = 0b0100,
    DataReadOnlyExpandDownAccessed = 0b0101,
    DataReadWriteExpandDown = 0b0110,
    DataReadWriteExpandDownAccessed = 0b0111,
    // Code Segments
    CodeExecuteOnly = 0b1000,
    CodeExecuteOnlyAccessed = 0b1001,
    CodeExecuteRead = 0b1010,
    CodeExecuteReadAccessed = 0b1011,
    CodeExecuteOnlyConforming = 0b1100,
    CodeExecuteOnlyConformingAccessed = 0b1101,
    CodeExecuteReadConforming = 0b1110,
    CodeExecuteReadConformingAccessed = 0b1111
};

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
    static void set_limit(const std::uint32_t limit, Descriptors<Size>::Entry &descriptor);
    static void set_limit(Descriptors<Size>::Entry &descriptor);
    static void set_flags(const std::uint8_t flags, Descriptors<Size>::Entry &descriptor);
    static void set_access_byte(const std::uint16_t flags, Descriptors<Size>::Entry &descriptor);

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
    entry.base_address_low = (lower_mask & base);

    const std::uint32_t middle_mask = 0x00FF0000;
    const std::uint8_t middle_shift = 16;
    entry.base_address_mid = (middle_mask & base) >> middle_shift;

    const std::uint32_t high_mask = 0xFF000000;
    const std::uint8_t high_shift = 24;
    entry.base_address_high = (high_mask & base) >> high_shift;
}

template<std::uint8_t Size>
void Descriptors<Size>::set_limit(const std::uint32_t limit, Descriptors<Size>::Entry &descriptor)
{
    TODO();
}

template<std::uint8_t Size>
void Descriptors<Size>::set_limit(Descriptors<Size>::Entry &descriptor)
{
    descriptor.segment_limit_low = 0xFFFF;
    descriptor.segment_limit_high = 0xF;
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
    entry.granularity = (g_mask & flags) >> g_shift;

    const std::uint8_t db_mask = 0b0100;
    const std::uint8_t db_shift = 2;
    entry.db = (db_mask & flags) >> db_shift;

    const std::uint8_t l_mask = 0b0010;
    const std::uint8_t l_shift = 1;
    entry.l_mask = (l_mask & flags) >> db_shift;

    const std::uint8_t r_mask = 0b0000;
    entry.reserved = r_mask & flags;
}

// Access Byte:
//     +---+----+---+---+---+---+---+
//     | 1 | 02 | 1 | 1 | 1 | 1 | 1 |
//     +---+----+---+---+---+---+---+
//     | P | DPL| S | E | DC| RW| A |
//     +---+----+---+---+---+---+---+
//                  | AKA Type      |
//                  +---+---+---+---+
template<std::uint8_t Size>
void Descriptors<Size>::set_access_byte(std::uint16_t flags, Descriptors<Size>::Entry &entry)
{
    [[unlikely]] if (flags > 0xFF) {
        crash();
    }

    const std::uint8_t p_mask = 0b10000000;
    const std::uint8_t p_shift = 7;
    entry.present = (p_mask & flags) >> p_shift;

    const std::uint8_t dpl_mask = 0b01100000;
    const std::uint8_t dpl_shift = 5;
    entry.descriptor_privilege_level = (dpl_mask & flags) >> dpl_shift;

    const std::uint8_t s_mask = 0b00010000;
    const std::uint8_t s_shift = 4;
    entry.system = (s_mask & flags) >> s_shift;

    const std::uint8_t access_byte_mask = 0b00001111;
    const std::uint8_t access_byte_value = flags & access_byte_mask;
    entry.type = access_byte_value;
}

} // namespace Processor
