#pragma once

#include "Array.hpp"
#include "GraphicTypes.hpp"

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

    // TODO: Implement the following functions:
    //         uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
    //         uint16_t vga_entry(unsigned char uc, uint8_t color)
    //         size_t strlen(const char* str)
    //         void terminal_setcolor(uint8_t color)
    //         void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
    //         void terminal_putchar(char c)
    //         void terminal_write(const char* data, size_t size)
    //         void terminal_writestring(const char* data)
};
