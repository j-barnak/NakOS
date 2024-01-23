#include "kernel.hpp"
#include "Descriptor.hpp"
#include "Graphics.hpp"
#include "Processor/GDT.hpp"
#include <bit>

void kernel_main()
{
    auto gdtr = Processor::GDTR { .limit = 0, .base = std::bit_cast<void *>(0xFFFF) };
    auto gdt = Processor::GDT { gdtr };
    gdt.load_gtdr();

    auto null_descriptor = Processor::Descriptor { 0x0, 0x0 };

    gdt.push_descriptor_entry(null_descriptor);

    auto graphics = Graphics::Terminal {};
    char str[] = "Loaded GDT";
    graphics.write_string(str, 0, 0);
}
