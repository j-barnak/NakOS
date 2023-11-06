#include "Graphics.hpp"
#include "GraphicTypes.hpp"
#include <bit>

Graphics::Graphics() : m_column_position { 0 }, m_buffer { std::bit_cast<TerminalBuffer *>(0xb8000) }
{
    init_terminal();
}

void Graphics::init_terminal()
{
    auto initial_value = ScreenChar { static_cast<std::uint8_t>(' '), ColorCode { VGA_Color::White, VGA_Color::Black } };
    initial_value.disable_blinking();

    for (std::size_t y = 0; y < m_height; ++y) {
        for (std::size_t x = 0; x < m_width; ++x) {
            auto index = x * m_height + y;
            (*m_buffer)[index] = initial_value;
        }
        ++m_column_position;
    }
}

ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return ScreenChar { character, color };
}

ScreenChar Graphics::get_character(std::uint8_t character)
{
    return get_character(character, {});
}

void Graphics::write(const char *string)
{}
