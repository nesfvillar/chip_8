#pragma once

#include "instruction.hpp"
#include "parser.hpp"
#include "state.hpp"
#include "ui.hpp"

#include <algorithm>
#include <ranges>
#include <optional>
#include <variant>



namespace chip_8
{
    class Cpu
    {
    public:
        constexpr Cpu(IUserInterface& ui) noexcept :
            _ui(ui)
        {
        };

        constexpr Cpu(std::ranges::range auto const& program, IUserInterface& ui) noexcept :
                        _ui(ui)
        {
        std::ranges::copy(
                program,
                _state.memory.begin() + _state.PROGRAM_START);
        }

        ~Cpu() noexcept = default;

        std::optional<Instruction> constexpr next_operation() const noexcept
        {
            return decode(_state.fetch_instruction(_state.program_counter));
        }

        void execute_operation(Instruction const& operation) noexcept
        {
            _state.program_counter += 2;
            std::visit([this](auto const& op) noexcept
        {
                    op(_state, _ui);
                }, operation);
        }

    private:
        State _state;
        IUserInterface& _ui;
    };
}
