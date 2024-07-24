#pragma once

#include "operation.hpp"
#include "opcode.hpp"

#include <optional>
#include <ranges>


namespace chip_8
{
    std::optional<Operation> constexpr decode(Opcode const& opcode) noexcept
    {
        switch (opcode.a())
        {
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
        default:
            return std::nullopt;
        }
    }

    auto constexpr parse(std::ranges::viewable_range auto const& program) noexcept
    {
        return program
            | std::views::chunk(2)
            | std::views::transform([](auto&& o)
                {
                    return Opcode{ std::get<0>(o), std::get<1>(o) };
                })
            | std::views::transform(decode);
    }
}
