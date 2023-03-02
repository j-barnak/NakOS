#include "inc/Graphics.hpp"

Kernel::Graphics::ColorCode::ColorCode(Kernel::Graphics::VGA_Color foreground, Kernel::Graphics::VGA_Color background)
{
}

// We OR together two values to create one byte
// Each value has the possibility of being 4 bits wide (i.e., a nibble wide)
// The foreground nibble is the 4 most significant bits so we need to shift that left
// And the background bits are in the correct position so no need to shift
std::uint8_t Kernel::Graphics::ColorCode::determine_color(Kernel::Graphics::VGA_Color foreground, Kernel::Graphics::VGA_Color background)
{
    return static_cast<std::uint8_t>(background) | ( static_cast<std::uint8_t>(foreground) << 4);
}

