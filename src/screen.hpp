#pragma once

#include <array>
#include <cstdint>
#include <ranges>
#include <span>

namespace chip_8 {
using Sprite = uint8_t;

class Screen {
public:
  [[nodiscard]]
  auto const &buffer() const noexcept {
    return _buffer;
  }

  void constexpr clear_buffer() noexcept {
    for (auto &&row : _buffer)
      for (auto &&pixel : row)
        pixel = false;
  }

  bool constexpr draw_sprites(std::span<const Sprite> sprites, size_t x,
                              size_t y) noexcept {
    x %= WIDTH;
    y %= HEIGHT;

    bool collision = false;
    for (auto [i, sprite] : sprites | std::views::enumerate) {
      auto y_pixel = y + i;
      for (auto j = 7; j >= 0; j--) {
        auto x_pixel = x + 7 - j;
        auto pixel = (sprite & (1 << j)) >> j;

        collision |= _draw_pixel(pixel, x_pixel, y_pixel);
      }
    }

    return collision;
  }

private:
  bool constexpr _draw_pixel(bool pixel, size_t x, size_t y) noexcept {
    if (x >= WIDTH || y >= HEIGHT)
      return false;

    bool collision = _buffer[y][x] && (_buffer[y][x] == pixel);

    _buffer[y][x] = pixel && !collision;
    return collision;
  }

public:
  size_t static constexpr WIDTH = 64;
  size_t static constexpr HEIGHT = 32;

private:
  std::array<std::array<bool, WIDTH>, HEIGHT> _buffer{};
};
} // namespace chip_8
