#pragma once

#include "ui.hpp"

#include <span>

namespace chip_8
{
    constexpr size_t MEMORY_SIZE = 0x1000;
    using Memory = std::span<uint8_t, MEMORY_SIZE>;

    class Cpu
    {
    public:
        Cpu(Memory memory, IUserInterface &ui);

        ~Cpu();

    private:
        Memory _memory;
        IUserInterface &_ui;
    };
}