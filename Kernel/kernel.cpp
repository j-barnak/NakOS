#include "kernel.hpp"
#include "Graphics.hpp"

auto gdt = Processor::GDT<8> {};

void kernel_main()
{
    auto graphics = Graphics::Terminal {};
    char str[] = "Loaded GDT";
    graphics.write_string(str, 0, 0);
}
