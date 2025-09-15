#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate important structures, such as the IDT and the TSS
auto gdt = Processor::Descriptors<8> {};
auto tss = Processor::Descriptors<gdt.amount_of_entries()>::Entry {};

static void load_gdt_entries()
{
    // Links: - https://wiki.osdev.org/GDT_Tutorial
    //        - https://wiki.osdev.org/Global_Descriptor_Table

    // The following Segments for paging _and_ ignoring segmentation. Segmentation in long mode is ignored; and so it
    // makes doesn't make sense to account use segmentation.
    // - NULL descriptor
    // - Kernel Mode Code Segment
    // - Kernel Mode Data Segment
    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0x92
    //   - Flags:       0xC
    // - User Mode Code Segment
    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0xFA
    //   - Flags:       0xC
    // - User Mode Data Segment
    //   - Base:        std::addrof(tss)
    //   - Limit:       sizeof(tss) - 1
    //   - Access Byte: 0x89
    //   - Flags:       0x00

    constexpr auto size = gdt.amount_of_entries();

    // NOTE: - System descriptors (system field) are set to 0
    //       - Non-System are marked 1
    //       - DPL represents rings (0-3 with 0 being the most privileged)
    auto null_entry = Processor::Descriptors<size>::Entry {};

    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0x9A
    //     - 1 | 00 | 1 | 1 | 0 | 1 | 0
    //       P | DPL| S | E | DC| RW| A
    //   - Flags:       0xC
    //     - | 1 | 1 | 0 | 0 |
    //       | G | DB| L | R |
    auto kernel_mode_code_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = std::uint16_t { 0xFFFF },
        .base_address_low = std::uint16_t { 0x0000 },
        .base_address_mid = std::uint8_t { 0x00 },
        .type = std::uint8_t { 0x1 }, // TODO Need to verify
        .system = std::uint8_t { 0x1 },
        .descriptor_privilege_level = std::uint8_t { 0x0 },
        .present = std::uint8_t { 0x0 },
        .segment_limit_high = std::uint8_t { 0xF },
        .available = std::uint8_t { 0x1 }, // TODO Need to verify
        .reserved = std::uint8_t { 0x0 },
        .db = std::uint8_t { 0x0 },
        .granularity = std::uint8_t { 0x1 },
        .base_address_high = std::uint8_t { 0xFF },
    };

    auto kernel_mode_data_segment { 1 };


    gdt.load_descriptor_entry(null_entry, 0);
}

void gdt_init()
{
    gdt.load_gdtr();
    // NOTE: This is debugging information. To check if the GDT is loaded in the right place, uncomment the line of
    //       assembly and check what's on top of the stack with:
    //       (gdb) x/1xg $esp
    //
    //       asm volatile("sgdt 0x0(%esp);");
    load_gdt_entries();
}
