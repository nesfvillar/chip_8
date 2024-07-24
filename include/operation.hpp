#pragma once

#include "state.hpp"
#include "ui.hpp"

#include <random>
#include <variant>


namespace chip_8
{
    // 0NNN
    struct OpCallMCRoutine
    {
        constexpr OpCallMCRoutine(size_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        size_t const _location;
    };

    // 00E0
    struct OpClearScreen
    {
        void operator()(State&, IUserInterface& ui) const noexcept
        {
            ui.clear_screen();
        }
    };

    // 00EE
    struct OpReturnSubroutine
    {
        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto location = state.stack.back();

            state.program_counter = location;
            state.stack.pop_back();
        }
    };

    // 1NNN
    struct OpJump
    {
        constexpr OpJump(size_t location) noexcept : _location(location) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.program_counter = _location;
        }

    private:
        uint16_t const _location;
    };

    // 2NNN
    struct OpCallSubroutine
    {
        constexpr OpCallSubroutine(size_t location) noexcept : _location(location) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.stack.push_back(state.program_counter);
            state.program_counter = _location;
        }

    private:
        uint16_t const _location;
    };

    // 3XNN
    struct OpSkipIfEqValue
    {
        constexpr OpSkipIfEqValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            if (state.registers.at(_register) == _value)
            {
                state.program_counter += 2;
            }
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 4XNN
    struct OpSkipIfNotEqValue
    {
        constexpr OpSkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            if (state.registers.at(_register) != _value)
            {
                state.program_counter += 2;
            }
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 5XY0
    struct OpSkipIfEqRegister
    {
        constexpr OpSkipIfEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            if (x_value == y_value)
            {
                state.program_counter += 2;
            }
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 6XNN
    struct OpSetRegisterToValue
    {
        constexpr OpSetRegisterToValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.registers.at(_register) = _value;
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 7XNN
    struct OpAddRegisterValue
    {
        constexpr OpAddRegisterValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.registers.at(_register) += _value;
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 8XY0
    struct OpSetRegisterToRegister
    {
        constexpr OpSetRegisterToRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.registers.at(_x_register) = state.registers.at(_y_register);
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY1
    struct OpOr
    {
        constexpr OpOr(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value | y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY2
    struct OpAnd
    {
        constexpr OpAnd(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value & y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY3
    struct OpXor
    {
        constexpr OpXor(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value ^ y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY4
    struct OpAddRegisterRegister
    {
        constexpr OpAddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value + y_value;
            state.registers[0x0F] = 0xFFFF - x_value <= y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY5
    struct OpSubtractRegisterRegister
    {
        constexpr OpSubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value - y_value;
            state.registers[0x0F] = x_value > y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY6
    struct OpShiftRight
    {
        constexpr OpShiftRight(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_register);

            state.registers.at(_register) = x_value >> 1;
            state.registers[0x0F] = x_value & 1;
        }

    private:
        uint8_t const _register;
    };

    // 8XY7
    struct OpReverseSubtractRegisterRegister
    {
        constexpr OpReverseSubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = y_value - x_value;
            state.registers[0x0F] = y_value > x_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XYE
    struct OpShiftLeft
    {
        constexpr OpShiftLeft(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto value = state.registers.at(_register);

            state.registers.at(_register) = value << 1;
            state.registers[0x0F] = (value & (1 << 7)) > 0;
        }

    private:
        uint8_t const _register;
    };

    // 9XY0
    struct OpSkipIfNotEqRegister
    {
        constexpr OpSkipIfNotEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            if (x_value != y_value)
            {
                state.program_counter += 2;
            }
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // ANNN
    struct OpSet
    {
        constexpr OpSet(uint16_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint16_t const _location;
    };

    // BNNN
    struct OpJumpPlus
    {
        constexpr OpJumpPlus(uint16_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint16_t const _location;
    };

    // CXNN
    struct OpRandom
    {
        constexpr OpRandom(uint8_t reg, uint8_t mask, uint8_t random_value) noexcept :
            _register(reg),
            _mask(mask),
            _random_value(random_value) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            state.registers.at(_register) = _random_value & _mask;
        }

    private:
        uint8_t const _register;
        uint8_t const _mask;
        uint8_t const _random_value;
    };

    // DXYN
    struct OpDraw
    {
        constexpr OpDraw(uint8_t x_register, uint8_t y_register, uint8_t size) noexcept :
            _x_register(x_register),
            _y_register(y_register),
            _size(size) {}

        void operator()(State& state, IUserInterface& ui) const noexcept
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            std::vector<Sprite> sprites(state.memory.begin() + state.index, state.memory.begin() + state.index + _size);

            ui.draw(sprites, x_value, y_value);
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
        uint8_t const _size;
    };

    // EX9E
    struct OpSkipIfKeyPressed
    {
        constexpr OpSkipIfKeyPressed(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // EXA1
    struct OpSkipIfKeyNotPressed
    {
        constexpr OpSkipIfKeyNotPressed(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX07
    struct OpGetDelay
    {
        constexpr OpGetDelay(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto delay = state.timers[Timer::DELAY];

            state.registers.at(_register) = delay;
        }

    private:
        uint8_t const _register;
    };

    // FX0A
    struct OpGetKeyBlocking
    {
        constexpr OpGetKeyBlocking(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX15
    struct OpSetDelay
    {
        constexpr OpSetDelay(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::DELAY] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX18
    struct OpSetSound
    {
        constexpr OpSetSound(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::SOUND] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX1E
    struct OpAddToAdress
    {
        constexpr OpAddToAdress(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX29
    struct OpSetAdressToSprite
    {
        constexpr OpSetAdressToSprite(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX33
    struct OpStoreBCDAtAdress
    {
        constexpr OpStoreBCDAtAdress(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX55
    struct OpDumpRegisters
    {
        constexpr OpDumpRegisters(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    // FX65
    struct OpLoadRegisters
    {
        constexpr OpLoadRegisters(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept
        {
        }

    private:
        uint8_t const _register;
    };

    using Operation = std::variant <
        OpCallMCRoutine,
        OpClearScreen,
        OpReturnSubroutine,
        OpJump,
        OpCallSubroutine,
        OpSkipIfEqValue,
        OpSkipIfNotEqValue,
        OpSkipIfEqRegister,
        OpSetRegisterToValue,
        OpAddRegisterValue,
        OpSetRegisterToRegister,
        OpOr,
        OpAnd,
        OpXor,
        OpAddRegisterRegister,
        OpSubtractRegisterRegister,
        OpShiftRight,
        OpReverseSubtractRegisterRegister,
        OpShiftLeft,
        OpSkipIfNotEqRegister,
        OpSet,
        OpJumpPlus,
        OpRandom,
        OpDraw,
        OpSkipIfKeyPressed,
        OpSkipIfKeyNotPressed,
        OpGetDelay,
        OpGetKeyBlocking,
        OpSetDelay,
        OpSetSound,
        OpAddToAdress,
        OpSetAdressToSprite,
        OpStoreBCDAtAdress,
        OpDumpRegisters,
        OpLoadRegisters
    > ;
}
