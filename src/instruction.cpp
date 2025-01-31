#include "instruction.hpp"
#include <cassert>
#include <utility>

using namespace chip_8;

Instruction::~Instruction() noexcept = default;

CallMCRoutine::CallMCRoutine(size_t location) noexcept : _location(location) {}

void CallMCRoutine::operator()(Cpu &) const noexcept {}

void ClearScreen::operator()(Cpu &cpu) const noexcept {
  cpu.screen.clear_buffer();
}

void ReturnSubroutine::operator()(Cpu &cpu) const noexcept {
  assert(cpu.stack.size() > 0);

  auto location = cpu.stack.back();
  cpu.stack.pop_back();

  cpu.program_counter = location;
}

Jump::Jump(size_t location) noexcept : _location(location) {}

void Jump::operator()(Cpu &cpu) const noexcept {
  cpu.program_counter = _location;
}
CallSubroutine::CallSubroutine(size_t location) noexcept
    : _location(location) {}

void CallSubroutine::operator()(Cpu &cpu) const noexcept {
  try {
    cpu.stack.push_back(cpu.program_counter);
  } catch (const std::exception &) {
    assert(false);
  }

  cpu.program_counter = _location;
}

SkipIfEqValue::SkipIfEqValue(uint8_t reg, uint8_t value) noexcept
    : _register(reg), _value(value) {}

void SkipIfEqValue::operator()(Cpu &cpu) const noexcept {
  if (cpu.registers[_register] == _value) {
    cpu.step_program_counter();
  }
}

SkipIfNotEqValue::SkipIfNotEqValue(uint8_t reg, uint8_t value) noexcept
    : _register(reg), _value(value) {}

void SkipIfNotEqValue::operator()(Cpu &cpu) const noexcept {
  if (cpu.registers[_register] != _value) {
    cpu.step_program_counter();
  }
}

SkipIfEqRegister::SkipIfEqRegister(uint8_t x_register,
                                   uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void SkipIfEqRegister::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  if (x_value == y_value) {
    cpu.step_program_counter();
  }
}

SetRegisterToValue::SetRegisterToValue(uint8_t reg, uint8_t value) noexcept
    : _register(reg), _value(value) {}

void SetRegisterToValue::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_register] = _value;
}

AddRegisterValue::AddRegisterValue(uint8_t reg, uint8_t value) noexcept
    : _register(reg), _value(value) {}

void AddRegisterValue::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_register] += _value;
}

SetRegisterToRegister::SetRegisterToRegister(uint8_t x_register,
                                             uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void SetRegisterToRegister::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_x_register] = cpu.registers[_y_register];
}

Or::Or(uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void Or::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = x_value | y_value;
  cpu.set_flag(false);
}

And::And(uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void And::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = x_value & y_value;
  cpu.set_flag(false);
}

Xor::Xor(uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void Xor::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = x_value ^ y_value;
  cpu.set_flag(false);
}

AddRegisterRegister::AddRegisterRegister(uint8_t x_register,
                                         uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void AddRegisterRegister::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = x_value + y_value;
  cpu.set_flag(UINT8_MAX - x_value < y_value);
}

SubtractRegisterRegister::SubtractRegisterRegister(uint8_t x_register,
                                                   uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void SubtractRegisterRegister::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = x_value - y_value;
  cpu.set_flag(x_value >= y_value);
}

ShiftRight::ShiftRight(uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void ShiftRight::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_x_register] = cpu.registers[_y_register];

  auto x_value = cpu.registers[_x_register];
  cpu.registers[_x_register] >>= 1;
  cpu.set_flag((x_value & 1) > 0);
}

ReverseSubtractRegisterRegister::ReverseSubtractRegisterRegister(
    uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void ReverseSubtractRegisterRegister::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  cpu.registers[_x_register] = y_value - x_value;
  cpu.set_flag(y_value >= x_value);
}

ShiftLeft::ShiftLeft(uint8_t x_register, uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void ShiftLeft::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_x_register] = cpu.registers[_y_register];

  auto value = cpu.registers[_x_register];
  cpu.registers[_x_register] <<= 1;
  cpu.set_flag((value & (1 << 7)) > 0);
}

SkipIfNotEqRegister::SkipIfNotEqRegister(uint8_t x_register,
                                         uint8_t y_register) noexcept
    : _x_register(x_register), _y_register(y_register) {}

void SkipIfNotEqRegister::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  if (x_value != y_value) {
    cpu.step_program_counter();
  }
}

SetIndex::SetIndex(uint16_t location) noexcept : _location(location) {}

void SetIndex::operator()(Cpu &cpu) const noexcept { cpu.index = _location; }

JumpPlus::JumpPlus(uint16_t location) noexcept : _location(location) {}

void JumpPlus::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[0];

  cpu.program_counter = _location + value;
}

Random::Random(uint8_t reg, uint8_t random_value, uint8_t mask) noexcept
    : _register(reg), _random_value(random_value), _mask(mask) {}

void Random::operator()(Cpu &cpu) const noexcept {
  cpu.registers[_register] = _random_value & _mask;
}

Draw::Draw(uint8_t x_register, uint8_t y_register, uint8_t size) noexcept
    : _x_register(x_register), _y_register(y_register), _size(size) {}

void Draw::operator()(Cpu &cpu) const noexcept {
  auto x_value = cpu.registers[_x_register];
  auto y_value = cpu.registers[_y_register];

  auto sprites =
      cpu.memory | std::views::drop(cpu.index) | std::views::take(_size) |
      std::views::transform([](auto sprite) { return Sprite{sprite}; });

  cpu.set_flag(cpu.screen.draw_sprites(sprites, x_value, y_value));
}

SkipIfKeyPressed::SkipIfKeyPressed(uint8_t reg) noexcept : _register(reg) {}

void SkipIfKeyPressed::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  if (cpu.keyboard[value]) {
    cpu.step_program_counter();
  }
}

SkipIfKeyNotPressed::SkipIfKeyNotPressed(uint8_t reg) noexcept
    : _register(reg) {}

void SkipIfKeyNotPressed::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  if (!cpu.keyboard[value]) {
    cpu.step_program_counter();
  }
}

GetDelay::GetDelay(uint8_t reg) noexcept : _register(reg) {}

void GetDelay::operator()(Cpu &cpu) const noexcept {
  auto timer = std::to_underlying(Timer::DELAY);
  auto delay = cpu.timers[timer];

  cpu.registers[_register] = delay;
}

GetKeyBlocking::GetKeyBlocking(uint8_t reg) noexcept : _register(reg) {}

void GetKeyBlocking::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  for (auto [n, key] : cpu.keyboard | std::views::enumerate) {
    if (key) {
      cpu.registers[value] = n;
      return;
    }
  }

  cpu.step_program_counter(-1);
}

SetDelay::SetDelay(uint8_t reg) noexcept : _register(reg) {}

void SetDelay::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  auto delay = std::to_underlying(Timer::DELAY);
  cpu.timers[delay] = value;
}

SetSound::SetSound(uint8_t reg) noexcept : _register(reg) {}

void SetSound::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  auto sound = std::to_underlying(Timer::SOUND);
  cpu.timers[sound] = value;
}

AddToAdress::AddToAdress(uint8_t reg) noexcept : _register(reg) {}

void AddToAdress::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];

  cpu.index += value;
}

SetAdressToSprite::SetAdressToSprite(uint8_t reg) noexcept : _register(reg) {}

void SetAdressToSprite::operator()(Cpu &) const noexcept {}

StoreBCDAtAdress::StoreBCDAtAdress(uint8_t reg) noexcept : _register(reg) {}

void StoreBCDAtAdress::operator()(Cpu &cpu) const noexcept {
  auto value = cpu.registers[_register];
  auto bcda = _bcda(value);

  std::ranges::copy_n(bcda.rbegin(), _DIGITS_SIZE,
                      cpu.memory.begin() + cpu.index);
}

DumpRegisters::DumpRegisters(uint8_t reg) noexcept : _register(reg) {}

void DumpRegisters::operator()(Cpu &cpu) const noexcept {
  auto location = cpu.memory.begin() + cpu.index;

  try {
    std::ranges::copy_n(cpu.registers.begin(), _register + 1, location);
  } catch (const std::exception &) {
  }

  cpu.index += _register + 1;
}

LoadRegisters::LoadRegisters(uint8_t reg) noexcept : _register(reg) {}

void LoadRegisters::operator()(Cpu &cpu) const noexcept {
  auto location = cpu.memory.begin() + cpu.index;

  try {
    std::ranges::copy_n(location, _register + 1, cpu.registers.begin());
  } catch (const std::exception &) {
  }

  cpu.index += _register + 1;
}
