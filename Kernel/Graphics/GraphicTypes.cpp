#include "GraphicTypes.hpp"

ColorCode::ColorCode(VGA_Color foreground, VGA_Color background) 
    : color { determine_color(foreground, background) } 
{
}

ColorCode::ColorCode() 
    : ColorCode(VGA_Color::Green, VGA_Color::Red) 
{
}

// We OR together two values to create one byte
// Each value has the possibility of being 4 bits wide (i.e., a nibble wide)
// The foreground nibble is the 4 most significant bits so we need to shift that left
// And the background bits are in the correct position so no need to shift
std::uint8_t ColorCode::determine_color(VGA_Color foreground, VGA_Color background)
{
    return static_cast<std::uint8_t>(background) | ( static_cast<std::uint8_t>(foreground) << 4);
}
