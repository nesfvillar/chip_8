#pragma once

#include "cpu.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

#include <random>
#include <ranges>

namespace chip_8 {
struct State {
  Cpu cpu;
  Screen screen;
  Keyboard keyboard;

  constexpr State() noexcept = default;

  constexpr State(std::ranges::view auto program) : cpu(program) {}

  uint8_t random_value() noexcept {
    std::uniform_int_distribution uniform_distribution;

    return uniform_distribution(_random_engine);
  }

private:
  std::default_random_engine _random_engine{std::random_device{}()};
};
} // namespace chip_8
