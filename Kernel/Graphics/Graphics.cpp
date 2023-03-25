#include "Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) },
      buf { reinterpret_cast<tbuf*>(0xb8000) }
{
}

void Graphics::init_terminal()
{
    auto initial_value = ScreenChar{ static_cast<std::uint8_t>('a'), ColorCode{ VGA_Color::White, VGA_Color::Black } };

    for (std::size_t y = 0; y < m_height; ++y) {
        for (std::size_t x = 0; x < m_width; ++x) {
            auto idx = x * m_height + y;
            (*buf)[idx] = initial_value;
            //(*m_buffer)[y][x] = initial_value;
            ++m_column_position;
        }
    }
}

ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return  ScreenChar { character, color };
}

ScreenChar Graphics::get_character(std::uint8_t character)
{
    return  get_character(character, {} );
}
