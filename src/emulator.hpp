#pragma once

#include "opcode.hpp"
#include "state.hpp"

#include <filesystem>
#include <fstream>
#include <vector>

namespace chip_8 {

class Emulator {
public:
  Emulator(std::filesystem::path const &path)
      : _state(std::views::all(_read_binary(path))) {}

private:
  std::vector<uint8_t> _read_binary(std::filesystem::path const &path) {
    std::ifstream ifstream{path, std::ios::binary};
    std::istreambuf_iterator<char> it{ifstream}, end;

    return std::vector<uint8_t>(it, end);
  }

  [[nodiscard]]
  Opcode constexpr fetch_opcode(uint16_t location) const {
    return Opcode{_state.cpu.fetch_word(location)};
  }

private:
  State _state;
};
} // namespace chip_8
