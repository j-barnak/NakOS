#include "inc/Graphics.hpp"

// TODO: Need to finish
void Graphics::init_terminal() 
{
    auto initial_term_color = ColorCode {};
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            // *m_buffer[i][j] = initial_term_color;
        }
    }
}
