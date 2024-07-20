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

    auto constexpr parse(std::ranges::viewable_range auto&& program) noexcept
    {
        auto const separate_byte = [](uint8_t byte)
            {
                return std::array<uint8_t, 2>{(byte & 0xF0) >> 4, byte & 0x0F};
            };

        auto nibbles = program
            | std::views::transform(separate_byte)
            | std::views::join;

        return nibbles
            | std::views::chunk(4)
            | std::views::transform([](auto&& o) {return tokenize(o);})
            | std::views::filter([](auto&& o) { return o.has_value(); })
            | std::views::transform([](auto&& o) { return std::move(o.value()); });
    }
}
