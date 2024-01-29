#include "Processor/x86_init.hpp"
#include "Processor/Descriptors.hpp"
#include <cstdint>

// NOTE: Should be global because it needs to persist throughout the lifetime of the kernel. If it's in automatic
//       storage, the descriptors would deallocate important structures, such as the IDT and TSS.
auto gdt = Processor::Descriptors<8> {};

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
