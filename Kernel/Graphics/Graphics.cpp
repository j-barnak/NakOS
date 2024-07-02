#include "Graphics/Graphics.hpp"
#include <bit>
#include <cstddef>
#include <cstdint>

Graphics::Terminal::Terminal() : buffer { std::bit_cast<std::uint16_t *>(0xb8000) }
{
    initialize_terminal();
}

void Graphics::Terminal::initialize_terminal()
{
    auto sc = ScreenCharacter { .background = Color::Red, .foreground = Color::Green, .ascii = ' ' };
    auto screen_character = sc.to_16();


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

void Graphics::Terminal::write_string(char str[], std::size_t x, std::size_t y)
{
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
        auto sc = ScreenCharacter { .background = Graphics::Color::Blue, .foreground = Graphics::Color::Black, .ascii = static_cast<unsigned char>(str[i]) };
        buffer[m_width * y + x] = sc.to_16();
        ++x;
    }
}
