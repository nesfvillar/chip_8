cmake_minimum_required(VERSION 3.20.0)
project(chip-8 VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED)

add_executable(emulator src/emulator.cpp src/ui.cpp)
target_include_directories(emulator PRIVATE include)

if(MSVC)
  target_compile_options(emulator PRIVATE /W4 /WX)
else()
  target_compile_options(emulator PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
