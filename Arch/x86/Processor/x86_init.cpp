#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate important structures, such as the IDT and the TSS
auto gdt = Processor::Descriptors<8> {};
auto tss = Processor::Descriptors<gdt.amount_of_entries()>::Entry {};

static void load_gdt_entries()
{
    // TODO:  Entry 0 in a descriptor table, or the Null Descriptor, is never referenced by the processor, and should
    //        always contain no data. Certain emulators, like Bochs, will complain about limit exceptions if you do not
    //        have one present. Some use this descriptor to store a pointer to the GDT itself (to use with the LGDT
    //        instruction). The null descriptor is 8 bytes wide and the pointer is 6 bytes wide so it might just be the
    //        perfect place for this.
    //        A DPL 0 Code Segment descriptor (for your kernel)
    //        A Data Segment descriptor (writing to code segments is not allowed)
    //        A Task State Segment segment descriptor (its very useful to have at least one)
    //        Room for more segments if you need them (e.g. user-level, LDTs, more TSS, whatever)

    constexpr auto size = gdt.amount_of_entries();

    // NOTE: - System descriptors (system field) are set to 0
    //       - Non-System are marked 1
    //       - DPL represents rings (0-3 with 0 being the most privileged)
    auto null_entry = Processor::Descriptors<size>::Entry {};

    auto kernel_mode_code_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = 0,
        .base_address_low = 0,
        .base_address_mid = 0,
        .type = 10,
        .system = 1,
        .descriptor_privilege_level = 0,
        .present = 1,
        .segment_limit_high = 0,
        .available = 1,
        ._reserved = 0,
        .d_or_b = 1,
        .granularity = 1,
        .base_address_high = 0,
    };

    auto kernel_mode_data_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = 0,
        .base_address_low = 0,
        .base_address_mid = 0,
        .type = 6,
        .system = 1,
        .descriptor_privilege_level = 0,
        .present = 1,
        .segment_limit_high = 0,
        .available = 1,
        ._reserved = 0,
        .d_or_b = 0,
        .granularity = 0,
        .base_address_high = 0,
    };

    auto user_mode_code_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = 0,
        .base_address_low = 0,
        .base_address_mid = 0,
        .type = 10,
        .system = 1,
        .descriptor_privilege_level = 3,
        .present = 1,
        .segment_limit_high = 0,
        .available = 1,
        ._reserved = 0,
        .d_or_b = 1,
        .granularity = 1,
        .base_address_high = 0,
    };

    auto user_mode_data_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = 0,
        .base_address_low = 0,
        .base_address_mid = 0,
        .type = 6,
        .system = 1,
        .descriptor_privilege_level = 3,
        .present = 1,
        .segment_limit_high = 0,
        .available = 1,
        ._reserved = 0,
        .d_or_b = 0,
        .granularity = 0,
        .base_address_high = 0,
    };

    auto task_state_segment = Processor::Descriptors<size>::Entry {
        .segment_limit_low = 0,
        .base_address_low = 0,
        .base_address_mid = 0,
        .type = 2,
        .system = 1,
        .descriptor_privilege_level = 0,
        .present = 1,
        .segment_limit_high = 0,
        .available = 1,
        ._reserved = 0,
        .d_or_b = 0,
        .granularity = 0,
        .base_address_high = 0,
    };

    gdt.load_descriptor_entry(null_entry, 0);
    gdt.load_descriptor_entry(kernel_mode_code_segment, 1);
    gdt.load_descriptor_entry(kernel_mode_data_segment, 2);
    gdt.load_descriptor_entry(task_state_segment, 3);
}

void gdt_init()
{
    gdt.load_gtdr();
    // NOTE: This is debugging information. To check if the GDT is loaded in the right place, uncomment the line of
    //       assembly and check what's on top of the stack with:
    //       (gdb) x/1xg $esp
    //
    //       asm volatile("sgdt 0x0(%esp);");
    load_gdt_entries();
}
