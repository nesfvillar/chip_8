#pragma once

namespace chip_8
{
    struct IUserInterface
    {
        virtual ~IUserInterface() = default;
    };

    class CommandLineInterface : public IUserInterface
    {
    public:
    private:
    };
}