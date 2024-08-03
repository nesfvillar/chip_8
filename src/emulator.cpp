#include "cpu.hpp"
#include "instruction.hpp"
#include "ui.hpp"

#include <filesystem>
#include <fstream>
#include <raylib.h>
#include <vector>


using namespace chip_8;


auto read_binary(std::filesystem::path const& path)
{
    std::ifstream ifstream{ path, std::ios::binary };
    std::istreambuf_iterator<char> it{ ifstream }, end;

    return std::vector<uint8_t>(it, end);

    // return std::views::iota(it)
    // | std::views::take_while([end](auto&& i) { return i != end;})
    // | std::views::transform([](auto&& i) { return *i; });
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::exit(1);
    }

    auto program = read_binary(argv[1]);

    InitWindow(800, 600, "Chip-8 Emulator");
    SetTargetFPS(60);

    RaylibUserInterface ui{ };
    Cpu cpu{ program, ui };

    while (!WindowShouldClose())
    {
        ui.render();

        if (auto next = cpu.next_operation())
            cpu.execute_operation(*next);
        else
            CloseWindow();
    }
}
