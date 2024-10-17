#include "cpu.hpp"
#include "ui.hpp"

#include <filesystem>
#include <fstream>
#include <vector>

using namespace chip_8;

std::vector<uint8_t> read_binary(std::filesystem::path const &path) {
  std::ifstream ifstream{path, std::ios::binary};
  std::istreambuf_iterator<char> it{ifstream}, end;

  return std::vector<uint8_t>(it, end);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::exit(1);
  }

  auto program = read_binary(argv[1]);

  TerminalUserInterface ui{};
  Cpu cpu{program, ui};
}
