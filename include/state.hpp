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
        uint16_t static constexpr PROGRAM_START = 0x200;

        std::array<uint8_t, MEMORY_SIZE> memory{};
        std::array<uint8_t, REGISTERS_SIZE> registers{};
        std::array<uint8_t, TIMERS_SIZE> timers{};
        std::vector<uint16_t> stack{};
        uint16_t program_counter = PROGRAM_START;

        Opcode constexpr fetch_instruction(uint16_t location) const noexcept
        {
            auto high_byte = memory.at(location);
            auto low_byte = memory.at(location + 1);

            return Opcode{high_byte, low_byte};
        }
    };
}
