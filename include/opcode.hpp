#pragma once

#include "state.hpp"
#include "ui.hpp"


namespace chip_8
{
    struct IOpcode
    {
        void virtual operator()(State& state, IUserInterface& ui) const noexcept = 0;
        virtual ~IOpcode() noexcept = default;
    };

    // 0NNN
    struct OpCallMCRoutine : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        size_t const _location;
    };

    // 00E0
    struct OpClearScreen : public IOpcode
    {
        void operator()(State&, IUserInterface& ui) const noexcept override
        {
            ui.clear_screen();
        }
    };

    // 00EE
    struct OpReturnSubroutine : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }
    };

    // 1NNN
    struct OpJump : public IOpcode
    {

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.program_counter = _location;
        }

    private:
        uint16_t const _location;
    };

    // 2NNN
    struct OpCallSubroutine : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint16_t const _location;
    };

    // 3XNN
    struct OpSkipIfEqValue : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _value;
    };

    // 4XNN
    struct OpSkipIfNotEqValue : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _value;
    };

    // 5XY0
    struct OpSkipIfEqRegister : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 6XNN
    struct OpSetRegisterToValue : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 7XNN
    struct OpAddRegisterValue : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
        uint8_t const _value;
    };

    // 8XY0
    struct OpSetRegisterToRegister : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            state.registers.at(_x_register) = _y_register;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY1
    struct OpOr : public IOpcode
    {
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
    struct OpAnd : public IOpcode
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
    struct OpXor : public IOpcode
    {
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
    struct OpAddRegisterRegister : public IOpcode
    {
        constexpr OpAddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
            _x_register(x_register),
            _y_register(y_register) {}

        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value + y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY5
    struct OpSubtractRegisterRegister : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = x_value - y_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY6
    struct OpShiftRight : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XY7
    struct OpReverseSubtractRegisterRegister : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            state.registers.at(_x_register) = y_value - x_value;
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 8XYE
    struct OpShiftLeft : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // 9XY0
    struct OpSkipIfNotEqRegister : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // ANNN
    struct OpSet : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint16_t const _location;
    };

    // BNNN
    struct OpJumpPlus : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint16_t const _location;
    };

    // CXNN
    struct OpRandom : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // DXYN
    struct OpDraw : public IOpcode
    {
        void operator()(State& state, IUserInterface& ui) const noexcept override
        {
            auto x_value = state.registers.at(_x_register);
            auto y_value = state.registers.at(_y_register);

            // ui.draw(x, y, _nibbles[3]);
        }

    private:
        uint8_t const _x_register;
        uint8_t const _y_register;
    };

    // EX9E
    struct OpSkipIfKeyPressed : public IOpcode
    {
        void operator()(State& state, IUserInterface& ui) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // EXA1
    struct OpSkipIfKeyNotPressed : public IOpcode
    {
        void operator()(State& state, IUserInterface& ui) const noexcept override
        {
        }

    private:
        uint8_t const _x_register;
    };

    // FX07
    struct OpGetDelay : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto delay = state.timers[Timer::DELAY];

            state.registers.at(_register) = delay;
        }

    private:
        uint8_t const _register;
    };

    // FX0A
    struct OpGetKeyBlocking : public IOpcode
    {
        void operator()(State& state, IUserInterface& ui) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX15
    struct OpSetDelay : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::DELAY] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX18
    struct OpSetSound : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
            auto value = state.registers.at(_register);

            state.timers[Timer::SOUND] = value;
        }

    private:
        uint8_t const _register;
    };

    // FX1E
    struct OpAddToAdress : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX29
    struct OpSetAdressToSprite : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX33
    struct OpStoreBCDAtAdress : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX55
    struct OpDumpRegisters : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };

    // FX65
    struct OpLoadRegisters : public IOpcode
    {
        void operator()(State& state, IUserInterface&) const noexcept override
        {
        }

    private:
        uint8_t const _register;
    };
}
