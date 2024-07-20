#pragma once


namespace chip_8
{
    struct IUserInterface
    {
        virtual ~IUserInterface() noexcept = default;

        void virtual clear_screen() noexcept = 0;

        void virtual draw(size_t x, size_t y, unsigned height) noexcept = 0;
    };

    class CommandLineInterface : public IUserInterface
    {
    public:
    private:
    };
}
