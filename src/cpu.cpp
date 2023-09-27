#include "cpu.hpp"

using namespace chip_8;

Cpu::Cpu(Memory memory, IUserInterface &ui)
    : _memory(memory), _ui(ui){};

Cpu::~Cpu() = default;
