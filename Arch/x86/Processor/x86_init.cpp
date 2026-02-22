#include "Processor/x86_init.hpp"
#include "Error.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate important structures, such as the IDT and the TSS
auto gdt = Processor::Descriptors<8> {};
auto tss = Processor::Descriptors<gdt.amount_of_entries()>::Entry {};

static void load_gdt_entries()
{
    constexpr auto size = gdt.amount_of_entries();

    auto null_entry = Processor::Descriptors<size>::Entry {};

    // - Kernel Mode Data Segment
    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0x92
    //   - Flags:       0xC
    auto kernel_mode_code_segment = Processor::Descriptors<size>::Entry {};
    Processor::Descriptors<size>::set_limit(kernel_mode_code_segment);
    Processor::Descriptors<size>::set_base(0, kernel_mode_code_segment);
    Processor::Descriptors<size>::set_access_byte(0x92, kernel_mode_code_segment);
    Processor::Descriptors<size>::set_flags(0xC, kernel_mode_code_segment);

    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0x9A
    //     - 1 | 00 | 1 | 1 | 0 | 1 | 0
    //       P | DPL| S | E | DC| RW| A
    //   - Flags:       0xC
    //     - | 1 | 1 | 0 | 0 |
    //       | G | DB| L | R |
    auto kernel_mode_data_segment = Processor::Descriptors<size>::Entry {};
    Processor::Descriptors<size>::set_base(0, kernel_mode_data_segment);
    Processor::Descriptors<size>::set_limit(kernel_mode_data_segment);
    Processor::Descriptors<size>::set_access_byte(0x9A, kernel_mode_data_segment);
    Processor::Descriptors<size>::set_flags(0xC, kernel_mode_data_segment);

    // User Mode Code Segment
    // Offset = 0x0018
    // Base = 0
    // Limit = 0xFFFFF
    // Access Byte = 0xFA
    // Flags = 0xC
    auto user_mode_code_segment = Processor::Descriptors<size>::Entry {};
    Processor::Descriptors<size>::set_base(0, user_mode_code_segment);
    Processor::Descriptors<size>::set_limit(user_mode_code_segment);
    Processor::Descriptors<size>::set_access_byte(0xFA, user_mode_code_segment);
    Processor::Descriptors<size>::set_flags(0xC, user_mode_code_segment);

    // User Mode Data Segment
    // Offset = 0x0020
    // Base = 0
    // Limit = 0xFFFFF
    // Access Byte = 0xF2
    // Flags = 0xC
    auto user_mode_data_segment = Processor::Descriptors<size>::Entry {};
    Processor::Descriptors<size>::set_base(0, user_mode_data_segment);
    Processor::Descriptors<size>::set_limit(user_mode_data_segment);
    Processor::Descriptors<size>::set_access_byte(0xF2, user_mode_data_segment);
    Processor::Descriptors<size>::set_flags(0xC, user_mode_data_segment);

    // TSS
    // Offset = 0x0028
    // Base = &TSS
    // Limit = sizeof(TSS)-1
    // Access Byte = 0x89
    // Flags = 0x0
    Processor::Descriptors<size>::set_base(0, tss);
    Processor::Descriptors<size>::set_limit(tss);
    Processor::Descriptors<size>::set_access_byte(0x89, tss);
    Processor::Descriptors<size>::set_flags(0, tss);

    gdt.load_descriptor_entry(null_entry, 0);
    gdt.load_descriptor_entry(kernel_mode_code_segment, 1);
    gdt.load_descriptor_entry(kernel_mode_data_segment, 2);
    gdt.load_descriptor_entry(user_mode_code_segment, 3);
    gdt.load_descriptor_entry(user_mode_data_segment, 4);
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

    asm volatile("sgdt 0x0(%esp);");
}
