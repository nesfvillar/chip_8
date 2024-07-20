cmake_minimum_required(VERSION 3.5.0)
project(chip-8 VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)

include_directories(include)
add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
