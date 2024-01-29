#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate and important structures, such as the IDT and TSS.
auto gdt = Processor::Descriptors<8> {};

// Places
static void debug_registers(auto reg)
{
    asm volatile("mov %0, %%eax;" ::"m"(reg));
}

static void load_gdt_entries()
{
    constexpr auto size = gdt.amount_of_entries();

    // Null Entry
    auto entry_0 = Processor::Descriptors<size>::Entry {};
    // clang-format off
    auto entry_1 = Processor::Descriptors<size>::Entry {
      .segment_limit_low = 0xFFFF,  
      .base_address_low = 0xFFFF,
      .base_address_mid = 0xFF,
      .type = 0xF,
      .system = 0x1,
      .descriptor_privilege_level = 0x0,
      .present = 0x1,
      .segment_limit_high = 0x4,
      . available = 0x1,
      .d_or_b = 0x1,
      .granularity = 0x1,
      .base_address_high = 0xFF, 
    };
    // clang-format on
    debug_registers(entry_1);

    gdt.load_descriptor_entry(entry_0, 0);
    gdt.load_descriptor_entry(entry_1, 1);
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
