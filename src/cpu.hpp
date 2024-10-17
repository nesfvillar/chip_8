#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

namespace chip_8 {
enum Timer { DELAY, SOUND };

class Cpu {
public:
  constexpr Cpu(std::ranges::view auto program) {
    std::ranges::copy(program, memory.begin() + _PROGRAM_START);
  }

  [[nodiscard]]
  uint8_t fetch_byte(uint16_t location) const {
    return memory.at(location);
  }

  [[nodiscard]]
  uint16_t fetch_word(uint16_t location) const {
    return fetch_byte(location) << 4 | fetch_byte(location + 1);
  }

  void step_program_counter(uint16_t amount = 1) noexcept {
    program_counter += 2 * amount;
  }

  void set_flag(bool flag) noexcept { registers[_REGISTER_FLAG] = flag; }

private:
  size_t static constexpr _MEMORY_SIZE = 0x1000;
  uint16_t static constexpr _PROGRAM_START = 0x200;

  size_t static constexpr _REGISTERS_SIZE = 0x10;
  size_t static constexpr _REGISTER_FLAG = 0x0F;

  size_t static constexpr _TIMERS_SIZE = 0x2;

public:
  std::array<uint8_t, _MEMORY_SIZE> memory{};
  uint16_t program_counter = _PROGRAM_START;
  uint16_t index;

  std::array<uint8_t, _REGISTERS_SIZE> registers{};

  std::vector<uint16_t> stack{};

  std::array<uint8_t, _TIMERS_SIZE> timers{};
};
} // namespace chip_8
