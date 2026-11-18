//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#pragma once

#include <cstdint>
#include <string>

namespace rogue20 {

class WorldMap;

enum class Direction : std::uint8_t {
    North,
    East,
    West,
    South,
};

struct Player {
    std::string name = "Hero";
    int st = 10;
    int dx = 10;
    int iq = 10;
    int ht = 10;

    float x = 0.0f;
    float y = 0.0f;
    float size = 22.0f;
    float speed = 200.0f;
    Direction facing = Direction::South;
    bool isMoving = false;
    float animTime = 0.0f;

    void spawn();
    void update(float dt, const WorldMap& map);
};

}  // namespace rogue20
