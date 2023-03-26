#pragma once

#include "GraphicTypes.hpp"
#include "Array.hpp"
#include <bit>

class Graphics
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width  = 80;
    std::size_t m_column_position;

    using TerminalBuffer = Array<ScreenChar, m_height * m_width>;
    TerminalBuffer* m_buffer;

  public:
    Graphics();
    constexpr void init_terminal();
    // TODO: Implement
    // void enable_blinking();
    constexpr ScreenChar get_character(std::uint8_t character, ColorCode color);
    constexpr ScreenChar get_character(std::uint8_t character);
};

///
/// Definitions for Graphics
///
Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { std::bit_cast<TerminalBuffer*>(0xb8000) }
{
}

constexpr void Graphics::init_terminal()
{
    auto initial_value = ScreenChar{ static_cast<std::uint8_t>('t'), ColorCode{ VGA_Color::White, VGA_Color::Black } };

    for (std::size_t y = 0; y < m_height; ++y) {
        for (std::size_t x = 0; x < m_width; ++x) {
            auto index = x * m_height + y;
           (*m_buffer)[index] = initial_value; 
        }
        ++m_column_position;
    }
}

constexpr ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return  ScreenChar { character, color };
}

constexpr ScreenChar Graphics::get_character(std::uint8_t character)
{
    return  get_character(character, {} );
}
///
/// End Graphics Definitions
///
