#pragma once

#include "ui.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>
#include <vector>

namespace chip_8 {
enum Timer { DELAY, SOUND };

struct State {
public:
  constexpr State(UserInterface *ui) noexcept : ui(ui) {}

  constexpr State(std::ranges::range auto const &program,
                  UserInterface *ui) noexcept
      : State(ui) {
    std::ranges::copy(program, memory.begin() + _PROGRAM_START);
  }

private:
  uint16_t static constexpr _PROGRAM_START = 0x200;
  size_t static constexpr _MEMORY_SIZE = 0x1000;
  size_t static constexpr _REGISTERS_SIZE = 0x10;
  size_t static constexpr _TIMERS_SIZE = 0x2;

public:
  UserInterface *ui;

  std::array<uint8_t, _MEMORY_SIZE> memory{};
  std::array<uint8_t, _REGISTERS_SIZE> registers{};
  std::vector<uint16_t> stack{};
  std::array<uint8_t, _TIMERS_SIZE> timers{};
  uint16_t index = 0;
  uint16_t program_counter = _PROGRAM_START;
};
} // namespace chip_8
