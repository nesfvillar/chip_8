#pragma once

#include "instruction.hpp"
#include "parser.hpp"
#include "state.hpp"
#include "ui.hpp"

#include <ranges>
#include <optional>
#include <variant>


namespace chip_8
{
    class Cpu
    {
    public:
        constexpr Cpu(UserInterface& ui) noexcept :
            _ui(ui)
        {
        };

        constexpr Cpu(std::ranges::range auto const& program, UserInterface& ui) noexcept :
            _state(program),
            _ui(ui) {}

        ~Cpu() noexcept = default;

        std::optional<Instruction> constexpr next_operation() const noexcept
        {
            return decode(_state.fetch_instruction(_state.program_counter));
        }

        void execute_operation(Instruction const& operation) noexcept
        {
            _state.program_counter += 2;
            std::visit([this](auto const& op)
                {
                    op(_state, _ui);
                }, operation);
        }

    private:
        State _state;
        UserInterface& _ui;
    };
}
