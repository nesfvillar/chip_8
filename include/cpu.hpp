#pragma once

#include "ui.hpp"

#include <span>

namespace chip_8
{
    constexpr size_t MEMORY_SIZE = 0x1000;
    constexpr size_t REGISTERS_SIZE = 0x10;

    using Memory = std::span<uint8_t, MEMORY_SIZE>;
    using Register = uint8_t;
    using ProgramCounter = uint16_t;

    enum class TimersEnum
    {
        DELAY,
        SOUND
    };

    class Cpu
    {
    public:
        Cpu(Memory memory, IUserInterface &ui);

        Cpu(Memory memory, IUserInterface &ui, ProgramCounter pc);

        ~Cpu();

        const Register &get_register(unsigned register_n) const;

        const unsigned &get_timer(TimersEnum timer) const;

        IUserInterface &get_ui() const;

        void set_register(size_t register_n, unsigned value);

        void set_program_counter(size_t location);

        void set_timer(TimersEnum timer, unsigned value);

    private:
        Memory _memory;
        IUserInterface &_ui;
        ProgramCounter _pc;
    };
}