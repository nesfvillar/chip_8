#pragma once

#include <span>


namespace chip_8
{
    using Sprite = uint8_t;

    struct IUserInterface
    {
        virtual ~IUserInterface() noexcept = default;

        void virtual clear_screen() noexcept = 0;

        void virtual draw(std::span<const Sprite> sprites, size_t x, size_t y) noexcept = 0;
    };

    class CommandLineInterface : public IUserInterface
    {
    public:
    private:
    };
}
