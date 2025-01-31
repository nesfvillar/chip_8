#pragma once

#include "cpu.hpp"

#include <cmath>

namespace chip_8 {

struct Instruction {
  virtual ~Instruction() noexcept;
  virtual void operator()(Cpu &cpu) const noexcept = 0;
};

// 0NNN
struct CallMCRoutine final : public Instruction {
public:
  CallMCRoutine(size_t location) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  size_t _location;
};

// 00E0
struct ClearScreen : public Instruction {
  void operator()(Cpu &cpu) const noexcept override;
};

// 00EE
struct ReturnSubroutine : public Instruction {
  void operator()(Cpu &cpu) const noexcept override;
};

// 1NNN
struct Jump : public Instruction {
  Jump(size_t location) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint16_t _location;
};

// 2NNN
struct CallSubroutine : public Instruction {
  CallSubroutine(size_t location) noexcept;
  ~CallSubroutine() noexcept override = default;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint16_t _location;
};

// 3XNN
struct SkipIfEqValue : public Instruction {
  SkipIfEqValue(uint8_t reg, uint8_t value) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
  uint8_t _value;
};

// 4XNN
struct SkipIfNotEqValue : public Instruction {
  SkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
  uint8_t _value;
};

// 5XY0
struct SkipIfEqRegister : public Instruction {
  SkipIfEqRegister(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 6XNN
struct SetRegisterToValue : public Instruction {
  SetRegisterToValue(uint8_t reg, uint8_t value) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
  uint8_t _value;
};

// 7XNN
struct AddRegisterValue : public Instruction {
  AddRegisterValue(uint8_t reg, uint8_t value) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
  uint8_t _value;
};

// 8XY0
struct SetRegisterToRegister : public Instruction {
  SetRegisterToRegister(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY1
struct Or : public Instruction {
  Or(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY2
struct And : public Instruction {
  And(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY3
struct Xor : public Instruction {
  Xor(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY4
struct AddRegisterRegister : public Instruction {
  AddRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY5
struct SubtractRegisterRegister : public Instruction {
  SubtractRegisterRegister(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY6
struct ShiftRight : public Instruction {
  ShiftRight(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XY7
struct ReverseSubtractRegisterRegister : public Instruction {
  ReverseSubtractRegisterRegister(uint8_t x_register,
                                  uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 8XYE
struct ShiftLeft : public Instruction {
  ShiftLeft(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// 9XY0
struct SkipIfNotEqRegister : public Instruction {
  SkipIfNotEqRegister(uint8_t x_register, uint8_t y_register) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
};

// ANNN
struct SetIndex : public Instruction {
  SetIndex(uint16_t location) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint16_t _location;
};

// BNNN
struct JumpPlus : public Instruction {
  JumpPlus(uint16_t location) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint16_t _location;
};

// CXNN
struct Random : public Instruction {
  Random(uint8_t reg, uint8_t random_value, uint8_t mask) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
  uint8_t _random_value;
  uint8_t _mask;
};

// DXYN
struct Draw : public Instruction {
  Draw(uint8_t x_register, uint8_t y_register, uint8_t size) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _x_register;
  uint8_t _y_register;
  uint8_t _size;
};

// EX9E
struct SkipIfKeyPressed : public Instruction {
  SkipIfKeyPressed(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// EXA1
struct SkipIfKeyNotPressed : public Instruction {
  SkipIfKeyNotPressed(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX07
struct GetDelay : public Instruction {
  GetDelay(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX0A
struct GetKeyBlocking : public Instruction {
  GetKeyBlocking(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX15
struct SetDelay : public Instruction {
  SetDelay(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX18
struct SetSound : public Instruction {
  SetSound(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX1E
struct AddToAdress : public Instruction {
  AddToAdress(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX29
struct SetAdressToSprite : public Instruction {
  SetAdressToSprite(uint8_t reg) noexcept;

  void operator()(Cpu &) const noexcept override;

private:
  uint8_t _register;
};

// FX33
struct StoreBCDAtAdress : public Instruction {
  StoreBCDAtAdress(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

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
struct DumpRegisters : public Instruction {
  DumpRegisters(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};

// FX65
struct LoadRegisters : public Instruction {
  LoadRegisters(uint8_t reg) noexcept;

  void operator()(Cpu &cpu) const noexcept override;

private:
  uint8_t _register;
};
} // namespace chip_8
