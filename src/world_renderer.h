//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#pragma once

#include <SDL3/SDL.h>

#include "world_map.h"

namespace rogue20 {

void renderWorld(SDL_Renderer* renderer, const WorldMap& map, float cameraX,
                 float cameraY, float worldTime);

}  // namespace rogue20
