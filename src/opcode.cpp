#include "opcode.hpp"

using namespace chip_8;

class Opcode : public IOpcode
{
public:
    Opcode(std::span<unsigned, OPCODE_SIZE> nibbles) : _nibbles(nibbles) {}

protected:
    std::span<unsigned, OPCODE_SIZE> _nibbles;
};

// 0NNN
struct OpCallMCRoutine : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto location = _nibbles[3] + _nibbles[2] * 0x10 + _nibbles[1] * 0x100;
    }
};

// 00E0
struct OpClearScreen : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        cpu.get_ui().clear_screen();
    }
};

// 00EE
struct OpReturnSubroutine : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 1NNN
struct OpJump : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto location = _nibbles[3] + _nibbles[2] * 0x10 + _nibbles[1] * 0x100;
        cpu.set_program_counter(location);
    }
};

// 2NNN
struct OpCallSubroutine : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 3XNN
struct OpSkipIfEqValue : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 4XNN
struct OpSkipIfNotEqValue : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 5XY0
struct OpSkipIfEqRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 6XNN
struct OpSetRegisterToValue : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 7XNN
struct OpAddRegisterValue : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY0
struct OpSetRegisterToRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY1
struct OpOr : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], x | y);
    }
};

// 8XY2
struct OpAnd : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], x & y);
    }
};

// 8XY3
struct OpXor : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], x ^ y);
    }
};

// 8XY4
struct OpAddRegisterRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], x + y);
    }
};

// 8XY5
struct OpSubtractRegisterRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], x - y);
    }
};

// 8XY6
struct OpShiftRight : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY7
struct OpReverseSubtractRegisterRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.set_register(_nibbles[1], y - x);
    }
};

// 8XYE
struct OpShiftLeft : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// 9XY0
struct OpSkipIfNotEqRegister : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// ANNN
struct OpSet : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// BNNN
struct OpJumpPlus : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// CXNN
struct OpRandom : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// DXYN
struct OpDraw : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        auto y = cpu.get_register(_nibbles[2]);
        cpu.get_ui().draw(x, y, _nibbles[3]);
    }
};

// EX9E
struct OpSkipIfKeyPressed : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// EXA1
struct OpSkipIfKeyNotPressed : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX07
struct OpGetDelay : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto delay = cpu.get_timer(TimersEnum::DELAY);
        cpu.set_register(_nibbles[1], delay);
    }
};

// FX0A
struct OpGetKeyBlocking : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX15
struct OpSetDelay : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        cpu.set_timer(TimersEnum::DELAY, x);
    }
};

// FX18
struct OpSetSound : public Opcode
{
    void execute(Cpu &cpu) const override
    {
        auto x = cpu.get_register(_nibbles[1]);
        cpu.set_timer(TimersEnum::SOUND, x);
    }
};

// FX1E
struct OpAddToAdress : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX29
struct OpSetAdressToSprite : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX33
struct OpStoreBCDAtAdress : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX55
struct OpDumpRegisters : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

// FX65
struct OpLoadRegisters : public Opcode
{
    void execute(Cpu &cpu) const override
    {
    }
};

std::unique_ptr<const IOpcode> opcode_factory(std::span<unsigned, OPCODE_SIZE> nibbles)
{
}
