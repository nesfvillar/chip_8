#pragma once

#include "cpu.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

#include <ranges>

namespace chip_8 {
struct State {
public:
  constexpr State(std::ranges::view auto program) : Cpu(program) {}

private:
public:
  Cpu cpu;
  Screen screen;
  Keyboard keyboard;
};
} // namespace chip_8
