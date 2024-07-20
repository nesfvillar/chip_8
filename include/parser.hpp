#pragma once

#include "opcode.hpp"

#include <array>
#include <memory>
#include <optional>
#include <ranges>


namespace chip_8
{
    std::optional<std::unique_ptr<const IOpcode>> constexpr tokenize(std::ranges::viewable_range auto&& nibbles) noexcept
    {
        std::array<uint8_t, 4> values;
        for (auto&& [i, nibble] : nibbles | std::views::enumerate)
        {
            values[i] = nibble;
        }


        return std::nullopt;
    }

    std::array<uint8_t, 2> constexpr separate_byte(uint8_t byte)
    {
        return { (byte & 0xF0) >> 4, byte & 0x0F };
    }

    auto constexpr get_nibbles(std::ranges::viewable_range auto&& bytes)
            {
        return bytes
            | std::views::transform(separate_byte)
            | std::views::join;
    }

    auto constexpr parse_chunks(std::ranges::viewable_range auto&& program) noexcept
    {
        return get_nibbles(program)
            | std::views::chunk(4)
            | std::views::transform([](auto&& o) {return tokenize(o);});
    }

    auto constexpr parse_slides(std::ranges::viewable_range auto&& program) noexcept
    {
        return get_nibbles(program)
            | std::views::slide(4)
            | std::views::transform([](auto&& o) {return tokenize(o);});
    }
}
