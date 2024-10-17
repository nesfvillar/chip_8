#pragma once

#include "instruction.hpp"
#include "opcode.hpp"

#include <optional>

namespace chip_8 {
[[nodiscard]]
std::optional<Instruction> constexpr decode(Opcode const &opcode) noexcept {
  using namespace instruction;

  switch (opcode.a()) {
  case 0x0:
    switch (opcode.nnn()) {
    case 0x0E0:
      return ClearScreen{};
    case 0x0EE:
      return ReturnSubroutine{};
    default:
      return CallMCRoutine{opcode.nnn()};
    }
  case 0x1:
    return Jump{opcode.nnn()};
  case 0x2:
    return CallSubroutine{opcode.nnn()};
  case 0x3:
    return SkipIfEqValue{opcode.x(), opcode.nn()};
  case 0x4:
    return SkipIfNotEqValue{opcode.x(), opcode.nn()};
  case 0x5:
    if (opcode.n() == 0)
      return SkipIfEqRegister{opcode.x(), opcode.y()};
    else
      return std::nullopt;
  case 0x6:
    return SetRegisterToValue{opcode.x(), opcode.nn()};
  case 0x7:
    return AddRegisterValue{opcode.x(), opcode.nn()};
  case 0x8:
    switch (opcode.n()) {
    case 0x0:
      return SetRegisterToRegister{opcode.x(), opcode.y()};
    case 0x1:
      return Or{opcode.x(), opcode.y()};
    case 0x2:
      return And{opcode.x(), opcode.y()};
    case 0x3:
      return Xor{opcode.x(), opcode.y()};
    case 0x4:
      return AddRegisterRegister{opcode.x(), opcode.y()};
    case 0x5:
      return SubtractRegisterRegister{opcode.x(), opcode.y()};
    case 0x6:
      return ShiftRight{opcode.x()};
    case 0x7:
      return ReverseSubtractRegisterRegister{opcode.x(), opcode.y()};
    case 0xE:
      return ShiftLeft{opcode.x()};
    default:
      return std::nullopt;
    }
  case 0x9:
    if (opcode.n() == 0)
      return SkipIfNotEqRegister{opcode.x(), opcode.y()};
    else
      return std::nullopt;
  case 0xA:
    return SetIndex{opcode.nnn()};
  case 0xB:
    return JumpPlus{opcode.nnn()};
  case 0xC:
    return Random{opcode.x(), 0xFF, opcode.nn()};
  case 0xD:
    return Draw{opcode.x(), opcode.y(), opcode.n()};
  case 0xE:
    switch (opcode.nn()) {
    case 0x9E:
      return SkipIfKeyPressed{opcode.x()};
    case 0xA1:
      return SkipIfKeyNotPressed{opcode.x()};
    default:
      return std::nullopt;
    }
  case 0xF:
    switch (opcode.nn()) {
    case 0x0A:
      return GetKeyBlocking{opcode.x()};
    case 0x15:
      return SetDelay{opcode.x()};
    case 0x18:
      return SetSound{opcode.x()};
    case 0x1E:
      return AddToAdress{opcode.x()};
    case 0x29:
      return SetAdressToSprite{opcode.x()};
    case 0x33:
      return StoreBCDAtAdress{opcode.x()};
    case 0x55:
      return DumpRegisters{opcode.x()};
    case 0x65:
      return LoadRegisters{opcode.x()};
    default:
      return std::nullopt;
    }
  default:
    return std::nullopt;
  }
}
} // namespace chip_8
