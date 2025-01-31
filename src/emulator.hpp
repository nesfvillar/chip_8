#pragma once

#include "cpu.hpp"
#include "opcode.hpp"
#include "parser.hpp"

#include <filesystem>
#include <vector>

namespace chip_8 {

[[nodiscard]]
std::vector<uint8_t> read_binary(std::filesystem::path const &path);

class Emulator {
public:
  constexpr Emulator() noexcept = default;

  constexpr Emulator(std::ranges::view auto &&program) : cpu(program) {}

  void constexpr load_program(std::ranges::view auto &&program) {
    cpu = Cpu{program};
  }

  bool step();

  void decrease_timers() noexcept { return cpu.decrease_timers(); }

private:
  [[nodiscard]]
  std::optional<Opcode> constexpr fetch_opcode(
      uint16_t location) const noexcept {
    auto word = cpu.fetch<uint16_t>(location);
    return word.transform([](auto &&word) { return Opcode{word}; });
  }

  [[nodiscard]]
  std::optional<std::unique_ptr<Instruction>> constexpr fetch_instruction(
      uint16_t location) const noexcept {
    auto opcode = fetch_opcode(location);
    return opcode.and_then(decode);
  }

public:
  Cpu cpu;
};
} // namespace chip_8
