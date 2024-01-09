#pragma once

#include <cstdint>

// TODO: Implement:
//         1. a cursor position -- denotes the last [x, y] position we just wrote to
//         2. writes that begin at the last cursor position
//         3. New line awareness
//         4. if writes beging at a (line > m_height), then we clear the first line, shift everything up, and then write
//            a. probably want a shift() helper function

namespace Graphics {

enum class Color : std::uint16_t {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,
};

struct ScreenCharacter
{
    Color background;
    Color foreground;
    unsigned char ascii;

    std::uint16_t to_16() const;
};

class Terminal
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width = 80;
    std::size_t m_line_number = 0;
    std::size_t m_last_pos[25][80] = {};

    std::uint16_t *buffer;

    Color m_background;
    Color m_foreground;

    void initialize_terminal();
    void initialize_terminal(Color background, Color foreground);

  public:
    Terminal();
    Terminal(Color background, Color foreground);

    std::uint16_t to_screen_char(Color background, Color foreground, unsigned char ascii);
    std::uint16_t to_screen_char(ScreenCharacter screen_character);
};

}// namespace Graphics
