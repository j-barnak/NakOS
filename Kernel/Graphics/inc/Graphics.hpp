#pragma once

// Only a limited amount of headers are allowed
// becasuse we are in a Freestanding environment
// https://en.cppreference.com/w/cpp/freestanding
#include "inc/GraphicsTypes.hpp"

// VGA Text Mode
// Allows the ability to write to the terminal
// Based on:
// https://os.phil-opp.com/vga-text-mode/
// https://wiki.osdev.org/Bare_Bones

// TODO: We need to write to 0xb8000, so we should find the best way to write to 
//       that address. We have to write to the buffer, so we need to set that address
//       to where the IO is being performed. 
class Graphics
{
  private:
    // FIXME: Using static as a bandaid.
    //        find better ways to to implement
    static constexpr std::size_t m_width = 80;
    static constexpr std::size_t m_height = 25;
    std::size_t m_column_position;

    using TerminalBuffer = ScreenChar[m_width][m_height];
    TerminalBuffer* m_buffer;

  public:
    Graphics();
    void init_terminal();
    void write_byte(std::uint8_t);
    ScreenChar get_character(std::uint8_t character, ColorCode color);
};

