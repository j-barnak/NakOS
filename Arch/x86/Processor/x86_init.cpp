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
    // - NULL descriptor
    // - Kernel Mode Code Segment
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

    // - Kernel Mode Data Segment
    //   - Base:        0x0000
    //   - Limit:       0xFFFF
    //   - Access Byte: 0x92
    //   - Flags:       0xC
    // - User Mode Code Segment
    auto _kernel_mode_code_segment = Processor::Descriptors<size>::Entry {};
    Processor::Descriptors<size>::set_limit(_kernel_mode_code_segment);
    Processor::Descriptors<size>::set_base(0, _kernel_mode_code_segment);
    Processor::Descriptors<size>::set_access_byte(0x92, _kernel_mode_code_segment);
    Processor::Descriptors<size>::set_flags(0xC, _kernel_mode_code_segment);

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
    TODO();

    // User Mode Data Segment
    // Offset = 0x0020
    // Base = 0
    // Limit = 0xFFFFF
    // Access Byte = 0xF2
    // Flags = 0xC
    TODO();

    // TSS
    // Offset = 0x0028
    // Base = &TSS
    // Limit = sizeof(TSS)-1
    // Access Byte = 0x89
    // Flags = 0x0
    TODO();

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
