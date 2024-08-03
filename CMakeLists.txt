cmake_minimum_required(VERSION 3.24.0)
project(chip-8 VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        a8ec8472ff29b228f6c51b4156d140d4783fd33a
  FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)

add_executable(emulator src/emulator.cpp src/ui.cpp)
target_include_directories(emulator PUBLIC include)
target_compile_features(emulator PUBLIC cxx_std_23)
target_link_libraries(emulator raylib)

if(MSVC)
  target_compile_options(emulator PRIVATE /W4)
else()
  target_compile_options(emulator PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
