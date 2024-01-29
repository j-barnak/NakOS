#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate and important structures, such as the IDT and TSS.
auto gdt = Processor::Descriptors<8> {};

static void load_gdt_entries()
{
    constexpr auto size = gdt.amount_of_entries();

    // Null Entry
    auto entry_0 = Processor::Descriptors<size>::Entry {};
    gdt.load_descriptor_entry(entry_0, 0);
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
