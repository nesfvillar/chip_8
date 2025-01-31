#pragma once

#include "screen.hpp"

#include <algorithm>
#include <cstdint>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <vector>

namespace chip_8 {

enum class Timer { DELAY, SOUND };

class Cpu {
public:
  constexpr Cpu() noexcept = default;

  constexpr Cpu(std::ranges::input_range auto &&program) {
    std::ranges::move(program, memory.begin() + _PROGRAM_START);
  }

  constexpr ~Cpu() noexcept = default;

  template <typename T>
  [[nodiscard]]
  std::optional<T> constexpr fetch(size_t location) const noexcept {
    T result = 0;
    try {
      for (size_t i = 0; i < sizeof(T); i++) {
        result = result << 8 | memory.at(location + i);
      }
      return result;
    } catch (std::out_of_range const &ex) {
      return std::nullopt;
    }
  }

  void constexpr step_program_counter(ssize_t amount = 1) noexcept {
    program_counter += 2 * amount;
  }

  void constexpr decrease_timers() noexcept {
    for (auto &&timer : timers) {
      timer = std::min(0, timer - 1);
    }
  }

  void constexpr set_flag(bool flag) noexcept {
    registers[_REGISTER_FLAG] = flag;
  }

private:
  size_t static constexpr _MEMORY_SIZE = 0x1000;
  uint16_t static constexpr _PROGRAM_START = 0x200;

  size_t static constexpr _REGISTERS_SIZE = 0x10;
  size_t static constexpr _REGISTER_FLAG = 0x0F;

  size_t static constexpr _TIMERS_SIZE = 0x2;

  size_t static constexpr _KEYBOARD_SIZE = 0x10;

public:
  std::array<uint8_t, _MEMORY_SIZE> memory{};
  uint16_t program_counter = _PROGRAM_START;
  uint16_t index;

  std::array<uint8_t, _REGISTERS_SIZE> registers{};

  std::vector<uint16_t> stack;

  std::array<uint8_t, _TIMERS_SIZE> timers{};

  std::array<bool, _KEYBOARD_SIZE> keyboard{};
  Screen screen;
};
} // namespace chip_8
