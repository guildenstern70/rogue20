cmake_minimum_required(VERSION 4.4)
project(Rogue20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)

add_executable(Rogue20
    src/main.cpp
    src/game.cpp
    src/world_map.cpp
    src/world_renderer.cpp
    src/player.cpp
    src/player_renderer.cpp
    src/hud_renderer.cpp
    src/camera.cpp
)
target_include_directories(Rogue20 PRIVATE src)
target_link_libraries(Rogue20 PRIVATE SDL3::SDL3)
