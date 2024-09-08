#include "cpu.hpp"
#include "instruction.hpp"
#include "ui.hpp"

#include <filesystem>
#include <fstream>
#include <raylib.h>
#include <vector>

#include <ftxui/component/screen_interactive.hpp>

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
    using namespace ftxui;

    if (argc != 2)
    {
        std::exit(1);
    }

    auto program = read_binary(argv[1]);

    TerminalUserInterface ui{};
    Cpu cpu{program, ui};

    auto screen = ScreenInteractive::FitComponent();

    auto main_renderer = Renderer(
        [&]
        {
            for (auto i = 0; i < 11; i++)
            {
                auto next = cpu.next_operation();
                if (next)
                {
                    cpu.execute_operation(*next);
                    if (std::holds_alternative<instruction::Draw>(*next))
                    {
                        screen.RequestAnimationFrame();
                    }
                }
            }
            return ui.canvas();
        });

    screen.Loop(main_renderer | border);
}
