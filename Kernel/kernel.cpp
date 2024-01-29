#include "kernel.hpp"
#include "Graphics.hpp"

void kernel_main()
{
    auto graphics = Graphics::Terminal {};
    char str[] = "Loaded GDT";
    graphics.write_string(str, 0, 0);
}
