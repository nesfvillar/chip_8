#pragma once

#include "instruction.hpp"
#include "opcode.hpp"
#include "parser.hpp"
#include "state.hpp"
#include "ui.hpp"

#include <optional>
#include <ranges>

namespace chip_8 {
class Cpu {
public:
  constexpr Cpu(UserInterface *ui) noexcept : _state(ui) {};

  constexpr Cpu(std::ranges::range auto const &program,
                UserInterface *ui) noexcept
      : _state(program, ui) {}

  ~Cpu() noexcept = default;

  // void execute_operation(Instruction const operation) noexcept;

  void execute_operation(Instruction const operation) noexcept {
    _state.program_counter += 2;
    std::visit([this](auto const &op) { op(_state); }, operation);
  }

private:
  Opcode constexpr fetch_opcode(uint16_t location) const {
    auto high_byte = _state.memory.at(location);
    auto low_byte = _state.memory.at(location + 1);

    return Opcode{high_byte, low_byte};
  }

  std::optional<Instruction> constexpr next_operation() const noexcept {
    return decode(fetch_opcode(_state.program_counter));
  }

private:
  State _state;
};
} // namespace chip_8
