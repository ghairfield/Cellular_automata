cmake_minimum_required(VERSION 3.14)
project(Cellular_automata)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Cellular_automata src/main.cpp src/display.cpp src/display.h src/event.cpp src/event.h)
target_link_libraries(Cellular_automata ${SDL2_LIBRARY})