#include "cpu.hpp"
#include "instruction.hpp"
#include "ui.hpp"

#include <filesystem>
#include <fstream>
#include <ranges>


using namespace chip_8;

auto read_binary(std::filesystem::path const& path)
{
    std::ifstream x{ path, std::ios::binary };
    std::istreambuf_iterator<char> it{ x }, end;

    return std::views::iota(it)
        | std::views::take_while([end](auto&& i) { return i != end;})
        | std::views::transform([](auto&& e) { return *e; });
}

int main(int, char **)
{
}