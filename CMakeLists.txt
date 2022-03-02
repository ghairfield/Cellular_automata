cmake_minimum_required(VERSION 3.14)
project(Cellular_automata)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# I'm not sure what this does and it work without it....
#target_link_libraries(Cellular_automata PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_link_libraries(Cellular_automata PRIVATE SDL2_ttf)