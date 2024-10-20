#pragma once

#include "cpu.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

#include <ranges>

namespace chip_8 {
struct State {
  Cpu cpu;
  Screen screen;
  Keyboard keyboard;

  constexpr State(std::ranges::view auto program) : cpu(program) {}
};
} // namespace chip_8
