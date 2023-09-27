#include "opcode.hpp"

using namespace chip_8;

// 0NNN
class OpCallMCRoutine : public IOpcode
{
public:
    OpCallMCRoutine(size_t location) : _location(location) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    size_t _location;
};

// 00E0
class OpClearScreen : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 00EE
class OpReturnSubroutine : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 1NNN
class OpJump : public IOpcode
{
public:
    OpJump(size_t location) : _location(location) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    size_t _location;
};

// 2NNN
class OpCallSubroutine : public IOpcode
{
public:
    OpCallSubroutine(size_t location) : _location(location) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    size_t _location;
};

// 3XNN
class OpSkipIfEqLiteral : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 4XNN
class OpSkipIfNotEqLiteral : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 5XY0
class OpSkipIfEqRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 6XNN
class OpSetRegisterToLiteral : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 7XNN
class OpAddRegisterLiteral : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY0
class OpSetRegisterToRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY1
class OpOr : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY2
class OpAnd : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY3
class OpXor : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY4
class OpAddRegisterRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY5
class OpSubtractRegisterRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY6
class OpShiftRight : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XY7
class OpReverseSubtractRegisterRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 8XYE
class OpShiftLeft : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// 9XY0
class OpSkipIfNotEqRegister : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// ANNN
class OpSet : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// BNNN
class OpJumpPlus : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// CXNN
class OpRandom : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// DXYN
class OpDraw : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// EX9E
class OpSkipIfKeyPressed : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// EXA1
class OpSkipIfNotKeyPressed : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX07
class OpGetDelay : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX0A
class OpGetKeyBlocking : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX15
class OpSetDelay : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX18
class OpSetSound : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX1E
class OpAddToAdress : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX29
class OpSetAdressToSprite : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX33
class OpStoreBCDAtAdress : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX55
class OpDumpRegisters : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

// FX65
class OpLoadRegisters : public IOpcode
{
public:
    void execute(Cpu &cpu) const override
    {
    }
};

std::unique_ptr<const IOpcode> opcode_factory(std::span<uint8_t, OPCODE_SIZE> nibbles)
{
    return std::make_unique<OpJump>(OpJump(10));
}
