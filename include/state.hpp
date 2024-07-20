#pragma once

#include <array>
#include <cstdint>


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
        std::array<uint16_t, TIMERS_SIZE> timers{};
        uint16_t program_counter{};
    };
}
