#pragma once

#include "state.hpp"
#include "ui.hpp"

#include <random>


namespace chip_8
{
    struct IOperation
    {
        void virtual operator()(State& state, IUserInterface& ui) const noexcept = 0;
        virtual ~IOperation() noexcept = default;
    };

    // 0NNN
    struct OpCallMCRoutine : public IOperation
    {
        constexpr OpCallMCRoutine(size_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        size_t const _location;
    };

    // 00E0
    struct OpClearScreen : public IOperation
    {
        void operator()(State&, IUserInterface& ui) const noexcept override
        {
            ui.clear_screen();
        }
    };

    // 00EE
    struct OpReturnSubroutine : public IOperation
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto location = state.stack.back();

            state.program_counter = location;
            state.stack.pop_back();
        }
    };

    // 1NNN
    struct OpJump : public IOperation
    {
        constexpr OpJump(size_t location) noexcept : _location(location) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.program_counter = _location;
        }

    private:
        uint16_t const _location;
    };

    // 2NNN
    struct OpCallSubroutine : public IOperation
    {
        constexpr OpCallSubroutine(size_t location) noexcept : _location(location) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.stack.push_back(state.program_counter);
            state.program_counter = _location;
        }

    private:
        uint16_t const _location;
    };

    // 3XNN
    struct OpSkipIfEqValue : public IOperation
    {
        constexpr OpSkipIfEqValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpSkipIfNotEqValue : public IOperation
    {
        constexpr OpSkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpSkipIfEqRegister : public IOperation
    {
        constexpr OpSkipIfEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpSetRegisterToValue : public IOperation
    {
        constexpr OpSetRegisterToValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.registers.at(_register) = _value;
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 7XNN
    struct OpAddRegisterValue : public IOperation
    {
        constexpr OpAddRegisterValue(uint8_t reg, uint8_t value) noexcept :
            _register(reg),
            _value(value) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.registers.at(_register) += _value;
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 8XY0
    struct OpSetRegisterToRegister : public IOperation
    {
        constexpr OpSetRegisterToRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.registers.at(_x_register) = state.registers.at(_y_register);
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY1
    struct OpOr : public IOperation
    {
        constexpr OpOr(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpAnd : public IOperation
    {
        constexpr OpAnd(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpXor : public IOperation
    {
        constexpr OpXor(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpAddRegisterRegister : public IOperation
    {
        constexpr OpAddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpSubtractRegisterRegister : public IOperation
    {
        constexpr OpSubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpShiftRight : public IOperation
    {
        constexpr OpShiftRight(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto x_value = state.registers.at(_register);

            state.registers.at(_register) = x_value >> 1;
            state.registers[0x0F] = x_value & 1;
        }

    private:
        uint8_t const _register;
    };

    // 8XY7
    struct OpReverseSubtractRegisterRegister : public IOperation
    {
        constexpr OpReverseSubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpShiftLeft : public IOperation
    {
        constexpr OpShiftLeft(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto value = state.registers.at(_register);

            state.registers.at(_register) = value << 1;
            state.registers[0x0F] = (value & (1 << 7)) > 0;
        }

    private:
        uint8_t const _register;
    };

    // 9XY0
    struct OpSkipIfNotEqRegister : public IOperation
    {
        constexpr OpSkipIfNotEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
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
    struct OpSet : public IOperation
    {
        constexpr OpSet(uint16_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint16_t const _location;
    };

    // BNNN
    struct OpJumpPlus : public IOperation
    {
        constexpr OpJumpPlus(uint16_t location) noexcept : _location(location) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint16_t const _location;
    };

    // CXNN
    struct OpRandom : public IOperation
    {
        constexpr OpRandom(uint8_t reg, uint8_t mask, uint8_t random_value) noexcept :
            _register(reg),
            _mask(mask),
            _random_value(random_value) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.registers.at(_register) = _random_value & _mask;
        }

    private:
        uint8_t const _register;
        uint8_t const _mask;
        uint8_t const _random_value;
    };

    // DXYN
    struct OpDraw : public IOperation
    {
        constexpr OpDraw(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
            // auto x_value = state.registers.at(_x_register);
            // auto y_value = state.registers.at(_y_register);

            // ui.draw(x, y, _nibbles[3]);
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // EX9E
    struct OpSkipIfKeyPressed : public IOperation
    {
        constexpr OpSkipIfKeyPressed(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // EXA1
    struct OpSkipIfKeyNotPressed : public IOperation
    {
        constexpr OpSkipIfKeyNotPressed(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX07
    struct OpGetDelay : public IOperation
    {
        constexpr OpGetDelay(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto delay = state.timers[Timer::DELAY];

            state.registers.at(_register) = delay;
        }

    private:
        uint8_t const _register;
    };

    // FX0A
    struct OpGetKeyBlocking : public IOperation
    {
        constexpr OpGetKeyBlocking(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX15
    struct OpSetDelay : public IOperation
    {
        constexpr OpSetDelay(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::DELAY] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX18
    struct OpSetSound : public IOperation
    {
        constexpr OpSetSound(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::SOUND] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX1E
    struct OpAddToAdress : public IOperation
    {
        constexpr OpAddToAdress(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX29
    struct OpSetAdressToSprite : public IOperation
    {
        constexpr OpSetAdressToSprite(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX33
    struct OpStoreBCDAtAdress : public IOperation
    {
        constexpr OpStoreBCDAtAdress(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX55
    struct OpDumpRegisters : public IOperation
    {
        constexpr OpDumpRegisters(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX65
    struct OpLoadRegisters : public IOperation
    {
        constexpr OpLoadRegisters(uint8_t reg) noexcept : _register(reg) {}

        void operator()(State&, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };
}
