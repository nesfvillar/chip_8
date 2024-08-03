#include "ui.hpp"

#include <iostream>
#include <raylib.h>

using namespace chip_8;


void TerminalUserInterface::render() noexcept
{
    for (auto row : screen_buffer_)
    {
        for (auto pixel : row)
        {
            if (pixel) std::cout << '#';
            else std::cout << '.';
        }
        std::cout << '\n';
    }
}

void RaylibUserInterface::render() noexcept
{
    float pixel_width = GetRenderWidth() / WIDTH;
    float pixel_height = GetRenderHeight() / HEIGHT;

    BeginDrawing();

    for (auto [i, row] : screen_buffer_ | std::views::enumerate)
    {
        for (auto [j, pixel] : row | std::views::enumerate)
        {
            Vector2 position{ j * pixel_width, i * pixel_height };
            auto color = pixel ? WHITE : BLACK;
            DrawRectangleV(position, { pixel_width, pixel_height }, color);
        }
    }

    EndDrawing();
}
