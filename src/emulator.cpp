#include "emulator.hpp"

#include <fstream>

using namespace chip_8;

std::vector<uint8_t> chip_8::read_binary(std::filesystem::path const &path) {
  std::ifstream ifstream{path, std::ios::binary};
  std::istreambuf_iterator<char> it{ifstream}, end;

  return std::vector<uint8_t>(it, end);
}

bool Emulator::step() {
  auto instruction = fetch_instruction(cpu.program_counter);
  cpu.step_program_counter();

  if (instruction) {
    instruction->get()->operator()(cpu);
    return true;
  }

  return false;
}
