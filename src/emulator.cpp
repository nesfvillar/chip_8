#include "emulator.hpp"
#include "parser.hpp"

#include <fstream>
#include <variant>

using namespace chip_8;

std::vector<uint8_t> chip_8::read_binary(std::filesystem::path const &path) {
  std::ifstream ifstream{path, std::ios::binary};
  std::istreambuf_iterator<char> it{ifstream}, end;

  return std::vector<uint8_t>(it, end);
}

Emulator::Emulator(std::filesystem::path const &path)
    : Emulator(std::views::all(read_binary(path))) {}

void Emulator::step() {
  auto opcode = fetch_opcode(_state.cpu.program_counter);
  _state.cpu.step_program_counter();

  auto instruction = decode(opcode);
  if (instruction) {
    std::visit([this](auto &&i) { return i(_state); }, *instruction);
  }
}
