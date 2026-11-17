//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//

#pragma once

#include <SDL3/SDL.h>

#include "camera.h"
#include "player.h"
#include "world_map.h"

namespace rogue20 {

class Game {
public:
    ~Game();

    bool init();
    void run();

private:
    void update(float dt);
    void render();

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    WorldMap map_{};
    Player player_{};
    Camera camera_{};
    float worldTime_ = 0.0f;
};

}  // namespace rogue20
