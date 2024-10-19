#pragma once

#include "opcode.hpp"
#include "state.hpp"

#include <filesystem>
#include <vector>

namespace chip_8 {

[[nodiscard]]
std::vector<uint8_t> read_binary(std::filesystem::path const &path);

class Emulator {
public:
  constexpr Emulator(std::ranges::view auto const &program) : _state(program) {}

  State const &state() const noexcept { return _state; }

  bool step();

private:
  [[nodiscard]]
  Opcode constexpr fetch_opcode(uint16_t location) const {
    return Opcode{_state.cpu.fetch_word(location)};
  }

private:
  State _state;
};
} // namespace chip_8
