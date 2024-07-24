#pragma once

#include <opcode.hpp>

#include <array>
#include <cstdint>
#include <vector>


namespace chip_8
{
    size_t constexpr MEMORY_SIZE = 0x1000;
    size_t constexpr REGISTERS_SIZE = 0x10;
    size_t constexpr TIMERS_SIZE = 0x2;

    enum Timer
    {
        DELAY,
        SOUND
    };

    struct State
    {
        std::array<uint8_t, MEMORY_SIZE> memory{};
        std::array<uint8_t, REGISTERS_SIZE> registers{};
        std::array<uint8_t, TIMERS_SIZE> timers{};
        std::vector<uint16_t> stack{};
        uint16_t program_counter{};

        Opcode constexpr fetch_instruction() const noexcept
        {
            auto high_byte = memory.at(program_counter);
            auto low_byte = memory.at(program_counter + 1);

            return Opcode{high_byte, low_byte};
        }
    };
}
