#pragma once

#include "state.hpp"
#include "opcode.hpp"
#include "ui.hpp"


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

        void operator()(IOpcode const* const operation) noexcept
        {
            operation->operator()(_state, _ui);
        }

    private:
        State _state;
        IUserInterface& _ui;
    };
}