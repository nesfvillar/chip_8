#pragma once

#include "opcode.hpp"
#include "parser.hpp"
#include "state.hpp"

#include <filesystem>
#include <vector>

namespace chip_8 {

[[nodiscard]]
std::vector<uint8_t> read_binary(std::filesystem::path const &path);

class Emulator {
public:
  constexpr Emulator() noexcept = default;

  constexpr Emulator(std::ranges::view auto program) : _state(program) {}

  State const &state() const noexcept { return _state; }

  void constexpr load_program(std::ranges::view auto program) {
    _state = State{program};
  }

  void constexpr decrease_timers() noexcept {
    return _state.cpu.decrease_timers();
  }

  bool step();

private:
  [[nodiscard]]
  std::optional<Opcode> constexpr fetch_opcode(
      uint16_t location) const noexcept {
    auto word = _state.cpu.fetch_word(location);
    return word.transform([](auto word) { return Opcode{word}; });
  }

  [[nodiscard]]
  std::optional<Instruction> constexpr fetch_instruction(
      uint16_t location) const noexcept {
    auto opcode = fetch_opcode(location);
    return opcode.and_then(decode);
  }

private:
  State _state;
};
} // namespace chip_8
