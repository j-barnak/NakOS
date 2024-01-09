#include "kernel.hpp"
#include "Graphics.hpp"

void kernel_main()
{
    auto graphics = Terminal {};
    unsigned char str[] = { "string" };
    graphics.write_string(str);
}
