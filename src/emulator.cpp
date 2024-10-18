#include "emulator.hpp"

#include <fstream>

using namespace chip_8;

std::vector<uint8_t> read_binary(std::filesystem::path const &path) {
  std::ifstream ifstream{path, std::ios::binary};
  std::istreambuf_iterator<char> it{ifstream}, end;

  return std::vector<uint8_t>(it, end);
}

Emulator::Emulator(std::filesystem::path const &path)
    : Emulator(std::views::all(read_binary(path))) {}
