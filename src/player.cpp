//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "player.h"

#include <SDL3/SDL.h>

#include "config.h"
#include "world_map.h"

namespace rogue20 {

void Player::spawn() {
    x = 3.0f * kTileSize + (kTileSize - size) * 0.5f;
    y = 3.0f * kTileSize + (kTileSize - size) * 0.5f;
}

void Player::update(float dt, const WorldMap& map) {
    const bool* keys = SDL_GetKeyboardState(nullptr);
    float dx = 0.0f;
    float dy = 0.0f;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) dy -= 1.0f;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) dy += 1.0f;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) dx -= 1.0f;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) dx += 1.0f;

    if (dy < 0.0f) {
        facing = Direction::North;
    } else if (dy > 0.0f) {
        facing = Direction::South;
    } else if (dx < 0.0f) {
        facing = Direction::West;
    } else if (dx > 0.0f) {
        facing = Direction::East;
    }

    isMoving = (dx != 0.0f || dy != 0.0f);
    animTime = isMoving ? (animTime + dt) : 0.0f;

    if (dx != 0.0f && dy != 0.0f) {
        constexpr float invSqrt2 = 0.70710678f;
        dx *= invSqrt2;
        dy *= invSqrt2;
    }

    const float nextX = x + dx * speed * dt;
    if (!map.collidesWithRect(nextX, y, size)) {
        x = nextX;
    }

    const float nextY = y + dy * speed * dt;
    if (!map.collidesWithRect(x, nextY, size)) {
        y = nextY;
    }
}

}  // namespace rogue20
