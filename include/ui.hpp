#pragma once

namespace chip_8
{
    struct IUserInterface
    {
        virtual ~IUserInterface() = default;

        virtual void clear_screen() = 0;

        virtual void draw(size_t x, size_t y, unsigned height) = 0;
    };

    class CommandLineInterface : public IUserInterface
    {
    public:
    private:
    };
}