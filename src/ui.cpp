#include "ui.hpp"

#include <iostream>

using namespace chip_8;

void TerminalUserInterface::render() noexcept {
  for (auto row : screen_buffer_) {
    for (auto pixel : row) {
      if (pixel)
        std::cout << '#';
      else
        std::cout << '.';
    }
    std::cout << '\n';
  }
}
