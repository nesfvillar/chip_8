#pragma once

#include <bitset>
#include <cassert>
#include <ranges>

namespace chip_8 {
using Sprite = std::bitset<8>;

class Screen {
public:
  void constexpr clear_buffer() noexcept { _buffer.reset(); }

  bool constexpr draw_sprites(std::ranges::view auto const sprites, size_t x,
                              size_t y) noexcept {
    x %= WIDTH;
    y %= HEIGHT;

    bool collision = false;
    for (auto [row, sprite] : sprites | std::views::enumerate) {
      for (auto col = 0; col < 8; col++) {
        auto y_pixel = y + row;
        auto x_pixel = x + 7 - col;

        bool pixel = sprite[col];

        collision |= _draw_pixel(pixel, x_pixel, y_pixel);
      }
    }

    return collision;
  }

  [[nodiscard]]
  decltype(auto) operator[](size_t x, size_t y) noexcept {
    assert(x < WIDTH && y < HEIGHT);

    return _buffer[y * WIDTH + x];
  }

private:
  bool constexpr _draw_pixel(bool pixel, size_t x, size_t y) noexcept {
    if (x >= WIDTH || y >= HEIGHT) {
      return false;
    }

    auto collision = pixel && operator[](x, y);
    operator[](x, y) = pixel ^ operator[](x, y);

    return collision;
  }

public:
  size_t static constexpr WIDTH = 64;
  size_t static constexpr HEIGHT = 32;

private:
  std::bitset<WIDTH * HEIGHT> _buffer;
};
} // namespace chip_8
