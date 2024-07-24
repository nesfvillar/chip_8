#pragma once

#include "operation.hpp"
#include "parser.hpp"
#include "state.hpp"
#include "ui.hpp"

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

        constexpr Cpu(State const& state, IUserInterface& ui) noexcept :
            _state(state),
            _ui(ui)
        {
        };

        ~Cpu() noexcept = default;

        std::optional<Operation> constexpr next_operation() const noexcept
        {
            return decode(_state.fetch_instruction(_state.program_counter));
        }

        void execute_operation(Operation const& operation) noexcept
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
