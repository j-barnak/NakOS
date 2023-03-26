#pragma once

#include <cstddef>
#include <cstdint>

// Hardware text mode color constants. 
enum class VGA_Color : std::uint8_t {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    Light_Grey = 7,
    Dark_Grey = 8,
    Light_Blue = 9,
    Light_Green = 10,
    Light_Cyan = 11,
    Light_Red = 12,
    Light_Magenta = 13,
    Light_Brown = 14,
    White = 15
};

// Defines the full color 
#pragma pack(push, 1)
struct ColorCode
{
    std::uint8_t color;

    constexpr explicit ColorCode(VGA_Color foreground, VGA_Color background);
    constexpr ColorCode();

    constexpr std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);
};
#pragma pack(pop)

///
/// Definitions for ColorCode
///
constexpr ColorCode::ColorCode(VGA_Color foreground, VGA_Color background) 
    : color { determine_color(foreground, background) } 
{
}

constexpr ColorCode::ColorCode() 
    : ColorCode(VGA_Color::Green, VGA_Color::Red) 
{
}

// We OR together two values to create one byte
// Each value has the possibility of being 4 bits wide (i.e., a nibble wide)
// The foreground nibble is the 4 most significant bits so we need to shift that left
// And the background bits are in the correct position so no need to shift
constexpr std::uint8_t ColorCode::determine_color(VGA_Color foreground, VGA_Color background)
{
    return static_cast<std::uint8_t>(background) | ( static_cast<std::uint8_t>(foreground) << 4);
}
///
/// End ColorCode definitions
///

// Defines the actual characters on VGA Screen
#pragma pack(push, 1)
struct ScreenChar
{
    std::uint8_t ascii_char;
    ColorCode color_code;
};
#pragma pack(pop)
