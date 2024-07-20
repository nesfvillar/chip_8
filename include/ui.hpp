#pragma once


namespace chip_8
{
    struct IUserInterface
    {
        virtual ~IUserInterface() = default;

        void virtual clear_screen() = 0;

        void virtual draw(size_t x, size_t y, unsigned height) = 0;
    };

    class CommandLineInterface : public IUserInterface
    {
    public:
    private:
    };
}
