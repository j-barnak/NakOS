#pragma once

#include "Array.hpp"
#include "GraphicTypes.hpp"

// TODO: Implement the following functions:
//         uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
//         uint16_t vga_entry(unsigned char uc, uint8_t color)
//         size_t strlen(const char* str)
//         void terminal_setcolor(uint8_t color)
//         void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
//         void terminal_putchar(char c)
//         void terminal_write(const char* data, size_t size)
//         void terminal_writestring(const char* data)

// TODO: Adding Support for Newlines to Terminal Driver
//         The current terminal driver does not handle newlines. The VGA
//         text mode font stores another character at the location, since
//         newlines are never meant to be actually rendered: they are
//         logical entities. Rather, in terminal_putchar
//         check if c == '\n' and increment terminal_row and reset
//         terminal_column.

// TODO: Implementing Terminal Scrolling
//         In case the terminal is filled up, it will just go back to the
//         top of the screen. This is unacceptable for normal use. Instead,
//         it should move all rows up one row and discard the upper most,
//         and leave a blank row at the bottom ready to be filled up with
//         characters. Implement this.

class Graphics
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width = 80;

    std::size_t m_column_position;
    std::size_t m_row_position;

    using TerminalBuffer = Array<ScreenChar, m_height * m_width>;
    TerminalBuffer *m_buffer;

    void init_terminal();

  public:
    Graphics();
    ScreenChar get_character(std::uint8_t character, ColorCode color);
    ScreenChar get_character(std::uint8_t character);
    void write(Array<ScreenChar, 80> character);
};
