#pragma once

#include <array>
#include <cstdint>
#include <span>


namespace chip_8
{
    using Sprite = uint8_t;

    class UserInterface
    {
    public:
        virtual ~UserInterface() noexcept = default;

        void virtual clear_screen() noexcept;

        bool virtual draw(std::span<const Sprite> sprites, size_t x, size_t y) noexcept;

    private:
        bool constexpr _draw_pixel(bool pixel, size_t x, size_t y) noexcept
        {
            if (x >= WIDTH_ || y >= HEIGHT_)
                return false;

            bool collision = _screen_buffer[y][x] == pixel;

            _screen_buffer[y][x] ^= pixel;
            return collision;
        }

    public:
        size_t static constexpr WIDTH_ = 64;
        size_t static constexpr HEIGHT_ = 32;

    private:
        std::array<std::array<bool, WIDTH_>, HEIGHT_> _screen_buffer;
    };
}
