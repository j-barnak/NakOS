#include "Graphics/Graphics.hpp"
#include <bit>
#include <cstddef>
#include <cstdint>

Graphics::Terminal::Terminal() : buffer { std::bit_cast<std::uint16_t *>(0xb8000) }
{
    initialize_terminal();
}

Graphics::Terminal::Terminal(Color background, Color foreground) : buffer { std::bit_cast<std::uint16_t *>(0xb8000) }, m_background { background }, m_foreground { foreground }
{
    initialize_terminal(background, foreground);
}

std::uint16_t Graphics::Terminal::to_screen_char(Color background, Color foreground, unsigned char ascii)
{
    auto sc = ScreenCharacter { background, foreground, ascii };
    auto val = to_screen_char(sc);
    return val;
}

std::uint16_t Graphics::Terminal::to_screen_char(ScreenCharacter screen_character)
{
    auto foreground = screen_character.foreground;
    auto background = screen_character.background;
    auto ascii = screen_character.ascii;

    std::uint16_t color = static_cast<std::uint16_t>(foreground) | static_cast<std::uint16_t>(background) << 4;
    std::uint16_t character = static_cast<std::uint16_t>(ascii) | color << 8;

    return character;
}

void Graphics::Terminal::initialize_terminal()
{
    auto screen_character = to_screen_char(ScreenCharacter { .background = Color::White, .foreground = Color::Black, .ascii = ' ' });

    for (std::size_t y = 0; y < m_height; ++y) {
        for (std::size_t x = 0; x < m_width; ++x) {
            buffer[x * m_height + y] = screen_character;
        }
    }
}

void Graphics::Terminal::initialize_terminal(Color background, Color foreground)
{
    auto screen_character = to_screen_char(ScreenCharacter { .background = background, .foreground = foreground, .ascii = ' ' });

    for (std::size_t y = 0; y < m_height; ++y) {
        for (std::size_t x = 0; x < m_width; ++x) {
            buffer[x * m_height + y] = screen_character;
        }
    }
}

std::uint16_t Graphics::ScreenCharacter::to_16() const
{

    std::uint16_t color = static_cast<std::uint16_t>(foreground) | static_cast<std::uint16_t>(background) << 4;
    std::uint16_t character = static_cast<std::uint16_t>(ascii) | color << 8;

    return character;
}
