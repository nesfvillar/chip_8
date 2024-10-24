#include "emulator.hpp"

#include <fstream>
#include <variant>

using namespace chip_8;

std::vector<uint8_t> chip_8::read_binary(std::filesystem::path const &path) {
  std::ifstream ifstream{path, std::ios::binary};
  std::istreambuf_iterator<char> it{ifstream}, end;

  return std::vector<uint8_t>(it, end);
}

bool Emulator::step() {
  auto instruction = fetch_instruction(_state.cpu.program_counter);
  _state.cpu.step_program_counter();

  if (instruction) {
    std::visit([this](auto &&i) { return i(_state); }, *instruction);
    if (std::holds_alternative<instruction::Draw>(*instruction)) {
      return true;
    }
  }
  return false;
}
