#pragma once

#include "state.hpp"
#include "opcode.hpp"
#include "parser.hpp"
#include "ui.hpp"

#include <memory>
#include <optional>
#include <ranges>


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

        std::optional<std::unique_ptr<const IOpcode>> constexpr next_operation() const noexcept
        {
            auto const& memory = _state.memory | std::views::drop(_state.program_counter);
            auto operations = parse(memory);

            if (operations.begin() != operations.end())
            {
                return *operations.begin();
            }
            else {
                return std::nullopt;
            }
        }

        void execute_operation(IOpcode const* const operation) noexcept
        {
            operation->operator()(_state, _ui);
        }

    private:
        State _state;
        IUserInterface& _ui;
    };
}
