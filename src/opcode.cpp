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
class OpSkipIfEqValue : public IOpcode
{
public:
    OpSkipIfEqValue(unsigned x, unsigned value) : _x(x), _value(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _value;
};

// 4XNN
class OpSkipIfNotEqValue : public IOpcode
{
public:
    OpSkipIfNotEqValue(unsigned x, unsigned value) : _x(x), _value(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _value;
};

// 5XY0
class OpSkipIfEqRegister : public IOpcode
{
public:
    OpSkipIfEqRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 6XNN
class OpSetRegisterToValue : public IOpcode
{
public:
    OpSetRegisterToValue(unsigned x, unsigned value) : _x(x), _value(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _value;
};

// 7XNN
class OpAddRegisterValue : public IOpcode
{
public:
    OpAddRegisterValue(unsigned x, unsigned value) : _x(x), _value(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _value;
};

// 8XY0
class OpSetRegisterToRegister : public IOpcode
{
public:
    OpSetRegisterToRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY1
class OpOr : public IOpcode
{
public:
    OpOr(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY2
class OpAnd : public IOpcode
{
public:
    OpAnd(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY3
class OpXor : public IOpcode
{
public:
    OpXor(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY4
class OpAddRegisterRegister : public IOpcode
{
public:
    OpAddRegisterRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY5
class OpSubtractRegisterRegister : public IOpcode
{
public:
    OpSubtractRegisterRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY6
class OpShiftRight : public IOpcode
{
public:
    OpShiftRight(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XY7
class OpReverseSubtractRegisterRegister : public IOpcode
{
public:
    OpReverseSubtractRegisterRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 8XYE
class OpShiftLeft : public IOpcode
{
public:
    OpShiftLeft(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// 9XY0
class OpSkipIfNotEqRegister : public IOpcode
{
public:
    OpSkipIfNotEqRegister(unsigned x, unsigned y) : _x(x), _y(y) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
};

// ANNN
class OpSet : public IOpcode
{
public:
    OpSet(size_t value) : _location(value) {}
    void execute(Cpu &cpu) const override
    {
    }

private:
    size_t _location;
};

// BNNN
class OpJumpPlus : public IOpcode
{
public:
    OpJumpPlus(size_t value) : _location(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    size_t _location;
};

// CXNN
class OpRandom : public IOpcode
{
public:
    OpRandom(unsigned x, unsigned value) : _x(x), _value(value) {}
    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _value;
};

// DXYN
class OpDraw : public IOpcode
{
    OpDraw(unsigned x, unsigned y, unsigned value) : _x(x), _y(y), _value(value) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
    unsigned _y;
    unsigned _value;
};

// EX9E
class OpSkipIfKeyPressed : public IOpcode
{
public:
    OpSkipIfKeyPressed(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// EXA1
class OpSkipIfKeyNotPressed : public IOpcode
{
public:
    OpSkipIfKeyNotPressed(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX07
class OpGetDelay : public IOpcode
{
public:
    OpGetDelay(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX0A
class OpGetKeyBlocking : public IOpcode
{
public:
    OpGetKeyBlocking(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX15
class OpSetDelay : public IOpcode
{
public:
    OpSetDelay(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX18
class OpSetSound : public IOpcode
{
public:
    OpSetSound(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX1E
class OpAddToAdress : public IOpcode
{
public:
    OpAddToAdress(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX29
class OpSetAdressToSprite : public IOpcode
{
public:
    OpSetAdressToSprite(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX33
class OpStoreBCDAtAdress : public IOpcode
{
public:
    OpStoreBCDAtAdress(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX55
class OpDumpRegisters : public IOpcode
{
public:
    OpDumpRegisters(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

// FX65
class OpLoadRegisters : public IOpcode
{
public:
    OpLoadRegisters(unsigned x) : _x(x) {}

    void execute(Cpu &cpu) const override
    {
    }

private:
    unsigned _x;
};

std::unique_ptr<const IOpcode> opcode_factory(std::span<uint8_t, OPCODE_SIZE> nibbles)
{
}
