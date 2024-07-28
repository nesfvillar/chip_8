#pragma once

#include "state.hpp"
#include "ui.hpp"

#include <random>
#include <ranges>
#include <span>
#include <variant>


namespace chip_8
{
    namespace instruction
    {
        // 0NNN
        struct CallMCRoutine
        {
            constexpr CallMCRoutine(size_t location) noexcept : _location(location) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            size_t const _location;
        };

        // 00E0
        struct ClearScreen
        {
            void operator()(State&, UserInterface& ui) const noexcept
            {
                ui.clear_buffer();
            }
        };

        // 00EE
        struct ReturnSubroutine
        {
            void operator()(State& state, UserInterface&) const noexcept
            {
                auto location = state.stack.back();
                state.stack.pop_back();

                state.program_counter = location;
            }
        };

        // 1NNN
        struct Jump
        {
            constexpr Jump(size_t location) noexcept : _location(location) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.program_counter = _location;
            }

        private:
            uint16_t const _location;
        };

        // 2NNN
        struct CallSubroutine
        {
            constexpr CallSubroutine(size_t location) noexcept : _location(location) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.stack.push_back(state.program_counter);
                state.program_counter = _location;
            }

        private:
            uint16_t const _location;
        };

        // 3XNN
        struct SkipIfEqValue
        {
            constexpr SkipIfEqValue(uint8_t reg, uint8_t value) noexcept :
                _register(reg),
                _value(value) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct SkipIfNotEqValue
        {
            constexpr SkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept :
                _register(reg),
                _value(value) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct SkipIfEqRegister
        {
            constexpr SkipIfEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct SetRegisterToValue
        {
            constexpr SetRegisterToValue(uint8_t reg, uint8_t value) noexcept :
                _register(reg),
                _value(value) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.registers.at(_register) = _value;
            }

        private:
            uint8_t const _register;
            uint8_t const _value;
        };

        // 7XNN
        struct AddRegisterValue
        {
            constexpr AddRegisterValue(uint8_t reg, uint8_t value) noexcept :
                _register(reg),
                _value(value) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.registers.at(_register) += _value;
            }

        private:
            uint8_t const _register;
            uint8_t const _value;
        };

        // 8XY0
        struct SetRegisterToRegister
        {
            constexpr SetRegisterToRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.registers.at(_x_register) = state.registers.at(_y_register);
            }

        private:
            uint8_t const _x_register;
            uint8_t const _y_register;
        };

        // 8XY1
        struct Or
        {
            constexpr Or(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct And
        {
            constexpr And(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct Xor
        {
            constexpr Xor(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct AddRegisterRegister
        {
            constexpr AddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct SubtractRegisterRegister
        {
            constexpr SubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct ShiftRight
        {
            constexpr ShiftRight(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                auto x_value = state.registers.at(_register);

                state.registers.at(_register) = x_value >> 1;
                state.registers[0x0F] = x_value & 1;
            }

        private:
            uint8_t const _register;
        };

        // 8XY7
        struct ReverseSubtractRegisterRegister
        {
            constexpr ReverseSubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct ShiftLeft
        {
            constexpr ShiftLeft(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                auto value = state.registers.at(_register);

                state.registers.at(_register) = value << 1;
                state.registers[0x0F] = (value & (1 << 7)) > 0;
            }

        private:
            uint8_t const _register;
        };

        // 9XY0
        struct SkipIfNotEqRegister
        {
            constexpr SkipIfNotEqRegister(uint8_t x_register, uint8_t y_register) noexcept :
                _x_register(x_register),
                _y_register(y_register) {}

            void operator()(State& state, UserInterface&) const noexcept
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
        struct SetIndex
        {
            constexpr SetIndex(uint16_t location) noexcept : _location(location) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.index = _location;
            }

        private:
            uint16_t const _location;
        };

        // BNNN
        struct JumpPlus
        {
            constexpr JumpPlus(uint16_t location) noexcept : _location(location) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint16_t const _location;
        };

        // CXNN
        struct Random
        {
            constexpr Random(uint8_t reg, uint8_t mask, uint8_t random_value) noexcept :
                _register(reg),
                _mask(mask),
                _random_value(random_value) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                state.registers.at(_register) = _random_value & _mask;
            }

        private:
            uint8_t const _register;
            uint8_t const _mask;
            uint8_t const _random_value;
        };

        // DXYN
        struct Draw
        {
            constexpr Draw(uint8_t x_register, uint8_t y_register, uint8_t size) noexcept :
                _x_register(x_register),
                _y_register(y_register),
                _size(size) {}

            void operator()(State& state, UserInterface& ui) const noexcept
            {
                auto x_value = state.registers.at(_x_register);
                auto y_value = state.registers.at(_y_register);

                auto indices = state.memory
                    | std::views::drop(state.index)
                    | std::views::take(_size);

                state.registers[0xF] = ui.draw_sprites(std::span<Sprite>{ indices }, x_value, y_value);
            }

        private:
            uint8_t const _x_register;
            uint8_t const _y_register;
            uint8_t const _size;
        };

        // EX9E
        struct SkipIfKeyPressed
        {
            constexpr SkipIfKeyPressed(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // EXA1
        struct SkipIfKeyNotPressed
        {
            constexpr SkipIfKeyNotPressed(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX07
        struct GetDelay
        {
            constexpr GetDelay(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                auto delay = state.timers[Timer::DELAY];

                state.registers.at(_register) = delay;
            }

        private:
            uint8_t const _register;
        };

        // FX0A
        struct GetKeyBlocking
        {
            constexpr GetKeyBlocking(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX15
        struct SetDelay
        {
            constexpr SetDelay(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                auto value = state.registers.at(_register);

                state.timers[Timer::DELAY] = value;
            }

        private:
            uint8_t const _register;
        };

        // FX18
        struct SetSound
        {
            constexpr SetSound(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State& state, UserInterface&) const noexcept
            {
                auto value = state.registers.at(_register);

                state.timers[Timer::SOUND] = value;
            }

        private:
            uint8_t const _register;
        };

        // FX1E
        struct AddToAdress
        {
            constexpr AddToAdress(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX29
        struct SetAdressToSprite
        {
            constexpr SetAdressToSprite(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX33
        struct StoreBCDAtAdress
        {
            constexpr StoreBCDAtAdress(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX55
        struct DumpRegisters
        {
            constexpr DumpRegisters(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };

        // FX65
        struct LoadRegisters
        {
            constexpr LoadRegisters(uint8_t reg) noexcept : _register(reg) {}

            void operator()(State&, UserInterface&) const noexcept
            {
            }

        private:
            uint8_t const _register;
        };
    }

    using Instruction = std::variant <
        instruction::CallMCRoutine,
        instruction::ClearScreen,
        instruction::ReturnSubroutine,
        instruction::Jump,
        instruction::CallSubroutine,
        instruction::SkipIfEqValue,
        instruction::SkipIfNotEqValue,
        instruction::SkipIfEqRegister,
        instruction::SetRegisterToValue,
        instruction::AddRegisterValue,
        instruction::SetRegisterToRegister,
        instruction::Or,
        instruction::And,
        instruction::Xor,
        instruction::AddRegisterRegister,
        instruction::SubtractRegisterRegister,
        instruction::ShiftRight,
        instruction::ReverseSubtractRegisterRegister,
        instruction::ShiftLeft,
        instruction::SkipIfNotEqRegister,
        instruction::SetIndex,
        instruction::JumpPlus,
        instruction::Random,
        instruction::Draw,
        instruction::SkipIfKeyPressed,
        instruction::SkipIfKeyNotPressed,
        instruction::GetDelay,
        instruction::GetKeyBlocking,
        instruction::SetDelay,
        instruction::SetSound,
        instruction::AddToAdress,
        instruction::SetAdressToSprite,
        instruction::StoreBCDAtAdress,
        instruction::DumpRegisters,
        instruction::LoadRegisters
    > ;
}
