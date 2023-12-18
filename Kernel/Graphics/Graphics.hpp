#pragma once

#include "Graphics/Types.hpp"
#include <cstdint>

// TODO: Implement:
//         1. a cursor position -- denotes the last [x, y] position we just wrote to
//         2. writes that begin at the last cursor position
//         3. New line awareness
//         4. if writes beging at a (line > m_height), then we clear the first line, shift everything up, and then write
//            a. probably want a shift() helper function

class Graphics
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width = 80;
    std::size_t m_line_number = 0;
    std::size_t m_last_pos[25][80] = {};

    std::uint16_t *m_terminal_buffer;

    Color m_background;
    Color m_foreground;

    void initialize_terminal();
    void initialize_terminal(Color background, Color foreground);

  public:
    Graphics();
    Graphics(Color background, Color foreground);

    std::uint16_t to_screen_char(Color background, Color foreground, unsigned char ascii);
    std::uint16_t to_screen_char(ScreenCharacter screen_character);

    void write_string(unsigned char str[], std::size_t size);
    void write_string(unsigned char str[]);
};
