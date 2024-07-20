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
}
