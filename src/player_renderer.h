//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#pragma once

#include <SDL3/SDL.h>

#include "player.h"

namespace rogue20 {

void renderPlayer(SDL_Renderer* renderer, const Player& player, float cameraX,
                  float cameraY);

}  // namespace rogue20
