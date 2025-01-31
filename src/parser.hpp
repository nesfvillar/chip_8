#pragma once

#include "instruction.hpp"
#include "opcode.hpp"

#include <memory>
#include <optional>

namespace chip_8 {

[[nodiscard]]
std::optional<std::unique_ptr<Instruction>> constexpr decode(
    Opcode const &opcode) noexcept {
  switch (opcode.a()) {
  case 0x0:
    switch (opcode.nnn()) {
    case 0x0E0:
      return std::make_unique<ClearScreen>();
    case 0x0EE:
      return std::make_unique<ReturnSubroutine>();
    default:
      return std::make_unique<CallMCRoutine>(opcode.nnn());
    }
  case 0x1:
    return std::make_unique<Jump>(opcode.nnn());
  case 0x2:
    return std::make_unique<CallSubroutine>(opcode.nnn());
  case 0x3:
    return std::make_unique<SkipIfEqValue>(opcode.x(), opcode.nn());
  case 0x4:
    return std::make_unique<SkipIfNotEqValue>(opcode.x(), opcode.nn());
  case 0x5:
    if (opcode.n() == 0)
      return std::make_unique<SkipIfEqRegister>(opcode.x(), opcode.y());
    else
      return std::nullopt;
  case 0x6:
    return std::make_unique<SetRegisterToValue>(opcode.x(), opcode.nn());
  case 0x7:
    return std::make_unique<AddRegisterValue>(opcode.x(), opcode.nn());
  case 0x8:
    switch (opcode.n()) {
    case 0x0:
      return std::make_unique<SetRegisterToRegister>(opcode.x(), opcode.y());
    case 0x1:
      return std::make_unique<Or>(opcode.x(), opcode.y());
    case 0x2:
      return std::make_unique<And>(opcode.x(), opcode.y());
    case 0x3:
      return std::make_unique<Xor>(opcode.x(), opcode.y());
    case 0x4:
      return std::make_unique<AddRegisterRegister>(opcode.x(), opcode.y());
    case 0x5:
      return std::make_unique<SubtractRegisterRegister>(opcode.x(), opcode.y());
    case 0x6:
      return std::make_unique<ShiftRight>(opcode.x(), opcode.y());
    case 0x7:
      return std::make_unique<ReverseSubtractRegisterRegister>(opcode.x(),
                                                               opcode.y());
    case 0xE:
      return std::make_unique<ShiftLeft>(opcode.x(), opcode.y());
    default:
      return std::nullopt;
    }
  case 0x9:
    if (opcode.n() == 0)
      return std::make_unique<SkipIfNotEqRegister>(opcode.x(), opcode.y());
    else
      return std::nullopt;
  case 0xA:
    return std::make_unique<SetIndex>(opcode.nnn());
  case 0xB:
    return std::make_unique<JumpPlus>(opcode.nnn());
  case 0xC:
    return std::make_unique<Random>(opcode.x(), 0xFF, opcode.nn());
  case 0xD:
    return std::make_unique<Draw>(opcode.x(), opcode.y(), opcode.n());
  case 0xE:
    switch (opcode.nn()) {
    case 0x9E:
      return std::make_unique<SkipIfKeyPressed>(opcode.x());
    case 0xA1:
      return std::make_unique<SkipIfKeyNotPressed>(opcode.x());
    default:
      return std::nullopt;
    }
  case 0xF:
    switch (opcode.nn()) {
    case 0x07:
      return std::make_unique<GetDelay>(opcode.x());
    case 0x0A:
      return std::make_unique<GetKeyBlocking>(opcode.x());
    case 0x15:
      return std::make_unique<SetDelay>(opcode.x());
    case 0x18:
      return std::make_unique<SetSound>(opcode.x());
    case 0x1E:
      return std::make_unique<AddToAdress>(opcode.x());
    case 0x29:
      return std::make_unique<SetAdressToSprite>(opcode.x());
    case 0x33:
      return std::make_unique<StoreBCDAtAdress>(opcode.x());
    case 0x55:
      return std::make_unique<DumpRegisters>(opcode.x());
    case 0x65:
      return std::make_unique<LoadRegisters>(opcode.x());
    default:
      return std::nullopt;
    }
  default:
    return std::nullopt;
  }
}
} // namespace chip_8
