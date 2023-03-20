#pragma once

#include <cstddef>
#include <cstdint>

/* Hardware text mode color constants. */
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

/* Defines the full color */
struct ColorCode
{
    std::uint8_t color;
    ColorCode() = default;
    ColorCode(VGA_Color foreground, VGA_Color background);
    // Helper Method
    std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);
};

/* Defines the actual characters */
// TODO: Investigate this to see if this is correct
//       Why do I have ColorCode and ScreenChar? Are these 16-bytes? or is it one byte?
struct ScreenChar
{
    std::uint8_t ascii_char;
    ColorCode color_code;
};

template<std::size_t width, std::size_t height>
struct Buffer
{
    ScreenChar buffer[width][height];  
};
