#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

auto gdt = Processor::Descriptors<8> {};

static void load_gdt_entries()
{
    auto entry_0 = Processor::Descriptors<gdt.array_size()>::Entry {};
    // clang-format off
    auto entry_1 = Processor::Descriptors<gdt.array_size()>::Entry {
      .segment_limit_low = 0,  
      .base_address_low = 0,
      .base_address_mid = 0,
      .type = 0,
      .system = 0,
      .descriptor_privilege_level = 0,
      .present = 1,
      .segment_limit_high = 0,
      . available = 1,
      .d_or_b = 0,
      .granularity = 0,
      .base_address_high = 0
    };
    // clang-format on

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
