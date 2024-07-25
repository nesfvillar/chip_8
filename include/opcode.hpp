#pragma once

#include <cstdint>


namespace chip_8
{
    class Opcode
    {
    public:
        constexpr Opcode(uint16_t value) noexcept : _value(value) {}

        constexpr Opcode(uint8_t high_byte, uint8_t low_byte) noexcept :
            _value((high_byte << 8) | low_byte) {}

        uint8_t constexpr a() const noexcept { return _value >> 12; }

        uint8_t constexpr x() const noexcept { return (_value & 0x0F00) >> 8; }

        uint8_t constexpr y() const noexcept { return (_value & 0x00F0) >> 4; }

        uint8_t constexpr n() const noexcept { return _value & 0x000F; }

        uint16_t constexpr nnn() const noexcept { return _value & 0x0FFF; }

        uint8_t constexpr nn() const noexcept { return _value & 0x00FF; }

    private:
        uint16_t const _value;
    };
}
