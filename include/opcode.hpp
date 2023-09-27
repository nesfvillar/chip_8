#pragma once

#include "cpu.hpp"

#include <memory>
#include <span>

namespace chip_8
{
    constexpr size_t OPCODE_SIZE = 4;
    using NibbleSpan = std::span<unsigned, OPCODE_SIZE>;

    struct IOpcode
    {
        virtual void execute(Cpu &cpu) const = 0;
        virtual ~IOpcode() = default;
    };

    std::unique_ptr<const IOpcode> opcode_factory(NibbleSpan nibbles);
}
