#include "ui.hpp"

#include <ranges>


using namespace chip_8;

void UserInterface::clear_screen() noexcept
{
    for (auto&& row : _screen_buffer)
        for (auto&& pixel : row)
            pixel = false;
}


bool UserInterface::draw(std::span<const Sprite> sprites, size_t x, size_t y) noexcept
{
    bool collision = false;
    for (auto [i, sprite] : sprites | std::views::enumerate)
    {
        auto y_pixel = y + i;
        for (auto j = 7; j >= 0; j--)
        {
            auto x_pixel = x + j;
            auto pixel = (sprite & (1 << j)) >> j;

            collision |= _draw_pixel(pixel, x_pixel, y_pixel);
        }
    }

    return collision;
}


