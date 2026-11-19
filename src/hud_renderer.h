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

void renderHud(SDL_Renderer* renderer, const Player& player);

}  // namespace rogue20
