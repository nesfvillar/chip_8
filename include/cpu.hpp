#pragma once

#include "state.hpp"
#include "ui.hpp"

#include <span>

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

        void set_program_counter(size_t location);

        void set_timer(TimersEnum timer, unsigned value);

    private:
        State _state;
        IUserInterface& _ui;
    };
}