cmake_minimum_required(VERSION 3.24.0)
project(chip-8 VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG        cdf28903a7781f97ba94d30b79c3a4b0c97ccce7
)
FetchContent_MakeAvailable(ftxui)

add_executable(emulator src/emulator.cpp src/ui.cpp)
target_include_directories(emulator PUBLIC include)
target_link_libraries(emulator PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component)

if(MSVC)
  target_compile_options(emulator PRIVATE /W4)
else()
  target_compile_options(emulator PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
