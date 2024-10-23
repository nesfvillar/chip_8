#pragma once

#include <bitset>
#include <cstdint>

namespace chip_8 {
class Keyboard {
public:
  [[nodiscard]]
  decltype(auto) operator[](uint8_t n) noexcept {
    return _keys[n];
  }

public:
  uint8_t static constexpr SIZE = 0x10;

private:
  std::bitset<SIZE> _keys;
};

} // namespace chip_8
