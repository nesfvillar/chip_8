#pragma once

#include "state.hpp"

#include <algorithm>
#include <ranges>
#include <variant>

namespace chip_8 {
namespace instruction {
// 0NNN
struct CallMCRoutine {
  constexpr CallMCRoutine(size_t location) noexcept : _location(location) {}

  void operator()(State &) const noexcept {}

private:
  size_t _location;
};

// 00E0
struct ClearScreen {
  void operator()(State &state) const noexcept { state.screen.clear_buffer(); }
};

// 00EE
struct ReturnSubroutine {
  void operator()(State &state) const noexcept {
    auto location = state.cpu.stack.back();
    state.cpu.stack.pop_back();

    state.cpu.program_counter = location;
  }
};

// 1NNN
struct Jump {
  constexpr Jump(size_t location) noexcept : _location(location) {}

  void operator()(State &state) const noexcept {
    state.cpu.program_counter = _location;
  }

private:
  uint16_t _location;
};

// 2NNN
struct CallSubroutine {
  constexpr CallSubroutine(size_t location) noexcept : _location(location) {}

  void operator()(State &state) const {
    state.cpu.stack.push_back(state.cpu.program_counter);
    state.cpu.program_counter = _location;
  }

private:
  uint16_t _location;
};

// 3XNN
struct SkipIfEqValue {
  constexpr SkipIfEqValue(uint8_t reg, uint8_t value) noexcept
      : _register(reg), _value(value) {}

  void operator()(State &state) const noexcept {
    if (state.cpu.registers[_register] == _value) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _register;
  uint8_t _value;
};

// 4XNN
struct SkipIfNotEqValue {
  constexpr SkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept
      : _register(reg), _value(value) {}

  void operator()(State &state) const noexcept {
    if (state.cpu.registers[_register] != _value) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _register;
  uint8_t _value;
};

// 5XY0
struct SkipIfEqRegister {
  constexpr SkipIfEqRegister(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    if (x_value == y_value) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 6XNN
struct SetRegisterToValue {
  constexpr SetRegisterToValue(uint8_t reg, uint8_t value) noexcept
      : _register(reg), _value(value) {}

  void operator()(State &state) const noexcept {
    state.cpu.registers[_register] = _value;
  }

private:
  uint8_t _register;
  uint8_t _value;
};

// 7XNN
struct AddRegisterValue {
  constexpr AddRegisterValue(uint8_t reg, uint8_t value) noexcept
      : _register(reg), _value(value) {}

  void operator()(State &state) const noexcept {
    state.cpu.registers[_register] += _value;
  }

private:
  uint8_t _register;
  uint8_t _value;
};

// 8XY0
struct SetRegisterToRegister {
  constexpr SetRegisterToRegister(uint8_t x_register,
                                  uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    state.cpu.registers[_x_register] = state.cpu.registers[_y_register];
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY1
struct Or {
  constexpr Or(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = x_value | y_value;
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY2
struct And {
  constexpr And(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = x_value & y_value;
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY3
struct Xor {
  constexpr Xor(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = x_value ^ y_value;
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY4
struct AddRegisterRegister {
  constexpr AddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = x_value + y_value;
    state.cpu.set_flag(UINT8_MAX - x_value < y_value);
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY5
struct SubtractRegisterRegister {
  constexpr SubtractRegisterRegister(uint8_t x_register,
                                     uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = x_value - y_value;
    state.cpu.set_flag(x_value >= y_value);
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY6
struct ShiftRight {
  constexpr ShiftRight(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_register];

    state.cpu.registers[_register] = x_value >> 1;
    state.cpu.set_flag(x_value & 1);
  }

private:
  uint8_t _register;
};

// 8XY7
struct ReverseSubtractRegisterRegister {
  constexpr ReverseSubtractRegisterRegister(uint8_t x_register,
                                            uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    state.cpu.registers[_x_register] = y_value - x_value;
    state.cpu.set_flag(y_value >= x_value);
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XYE
struct ShiftLeft {
  constexpr ShiftLeft(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    state.cpu.registers[_register] = value << 1;
    state.cpu.set_flag((value & (1 << 7)) > 0);
  }

private:
  uint8_t _register;
};

// 9XY0
struct SkipIfNotEqRegister {
  constexpr SkipIfNotEqRegister(uint8_t x_register, uint8_t y_register) noexcept
      : _x_register(x_register), _y_register(y_register) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    if (x_value != y_value) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// ANNN
struct SetIndex {
  constexpr SetIndex(uint16_t location) noexcept : _location(location) {}

  void operator()(State &state) const noexcept { state.cpu.index = _location; }

private:
  uint16_t _location;
};

// BNNN
struct JumpPlus {
  constexpr JumpPlus(uint16_t location) noexcept : _location(location) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[0];

    state.cpu.program_counter = _location + value;
  }

private:
  uint16_t _location;
};

// CXNN
struct Random {
  constexpr Random(uint8_t reg, uint8_t mask) noexcept
      : _register(reg), _mask(mask) {}

  void operator()(State &state) const noexcept {
    state.cpu.registers[_register] = state.random_value() & _mask;
  }

private:
  uint8_t _register;
  uint8_t _mask;
};

// DXYN
struct Draw {
  constexpr Draw(uint8_t x_register, uint8_t y_register, uint8_t size) noexcept
      : _x_register(x_register), _y_register(y_register), _size(size) {}

  void operator()(State &state) const noexcept {
    auto x_value = state.cpu.registers[_x_register];
    auto y_value = state.cpu.registers[_y_register];

    auto sprites =
        state.cpu.memory | std::views::drop(state.cpu.index) |
        std::views::take(_size) |
        std::views::transform([](auto sprite) { return Sprite{sprite}; });

    state.cpu.set_flag(state.screen.draw_sprites(sprites, x_value, y_value));
  }

private:
  uint8_t _x_register;
  uint8_t _y_register;
  uint8_t _size;
};

// EX9E
struct SkipIfKeyPressed {
  constexpr SkipIfKeyPressed(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    if (state.keyboard[value]) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _register;
};

// EXA1
struct SkipIfKeyNotPressed {
  constexpr SkipIfKeyNotPressed(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    if (!state.keyboard[value]) {
      state.cpu.step_program_counter();
    }
  }

private:
  uint8_t _register;
};

// FX07
struct GetDelay {
  constexpr GetDelay(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto delay = state.cpu.timers[Timer::DELAY];

    state.cpu.registers[_register] = delay;
  }

private:
  uint8_t _register;
};

// FX0A
struct GetKeyBlocking {
  constexpr GetKeyBlocking(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    for (uint8_t n = 0; n < Keyboard::SIZE; n++) {
      if (state.keyboard[n]) {
        state.cpu.registers[value] = n;
        return;
      }
    }

    state.cpu.step_program_counter(-1);
  }

private:
  uint8_t _register;
};

// FX15
struct SetDelay {
  constexpr SetDelay(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    state.cpu.timers[Timer::DELAY] = value;
  }

private:
  uint8_t _register;
};

// FX18
struct SetSound {
  constexpr SetSound(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    state.cpu.timers[Timer::SOUND] = value;
  }

private:
  uint8_t _register;
};

// FX1E
struct AddToAdress {
  constexpr AddToAdress(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const noexcept {
    auto value = state.cpu.registers[_register];

    state.cpu.index += value;
  }

private:
  uint8_t _register;
};

// FX29
struct SetAdressToSprite {
  constexpr SetAdressToSprite(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &) const noexcept {}

private:
  uint8_t _register;
};

// FX33
struct StoreBCDAtAdress {
  constexpr StoreBCDAtAdress(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const {
    auto value = state.cpu.registers[_register];
    auto bcda = _bcda(value);

    std::ranges::copy_n(bcda.rbegin(), _DIGITS_SIZE,
                        state.cpu.memory.begin() + state.cpu.index);
  }

private:
  size_t static constexpr _DIGITS_SIZE = 3;

  [[nodiscard]]
  std::array<uint8_t, _DIGITS_SIZE> static constexpr _bcda(
      uint8_t value) noexcept {
    std::array<uint8_t, _DIGITS_SIZE> result;

    for (size_t i = 0; i < _DIGITS_SIZE; i++) {
      result[i] = value % 10;
      value = std::floor(value / 10);
    }

    return result;
  }

private:
  uint8_t _register;
};

// FX55
struct DumpRegisters {
  constexpr DumpRegisters(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const {
    auto location = state.cpu.memory.begin() + state.cpu.index;

    std::ranges::copy_n(state.cpu.registers.begin(), _register + 1, location);
  }

private:
  uint8_t _register;
};

// FX65
struct LoadRegisters {
  constexpr LoadRegisters(uint8_t reg) noexcept : _register(reg) {}

  void operator()(State &state) const {
    auto location = state.cpu.memory.begin() + state.cpu.index;

    std::ranges::copy_n(location, _register + 1, state.cpu.registers.begin());
  }

private:
  uint8_t _register;
};
} // namespace instruction

using Instruction = std::variant<
    instruction::CallMCRoutine, instruction::ClearScreen,
    instruction::ReturnSubroutine, instruction::Jump,
    instruction::CallSubroutine, instruction::SkipIfEqValue,
    instruction::SkipIfNotEqValue, instruction::SkipIfEqRegister,
    instruction::SetRegisterToValue, instruction::AddRegisterValue,
    instruction::SetRegisterToRegister, instruction::Or, instruction::And,
    instruction::Xor, instruction::AddRegisterRegister,
    instruction::SubtractRegisterRegister, instruction::ShiftRight,
    instruction::ReverseSubtractRegisterRegister, instruction::ShiftLeft,
    instruction::SkipIfNotEqRegister, instruction::SetIndex,
    instruction::JumpPlus, instruction::Random, instruction::Draw,
    instruction::SkipIfKeyPressed, instruction::SkipIfKeyNotPressed,
    instruction::GetDelay, instruction::GetKeyBlocking, instruction::SetDelay,
    instruction::SetSound, instruction::AddToAdress,
    instruction::SetAdressToSprite, instruction::StoreBCDAtAdress,
    instruction::DumpRegisters, instruction::LoadRegisters>;
} // namespace chip_8
