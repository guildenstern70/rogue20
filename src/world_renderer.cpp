//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "world_renderer.h"

#include <algorithm>
#include <cmath>

#include "config.h"

namespace rogue20 {

namespace {

void setDrawColor(SDL_Renderer* renderer, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void renderTile(SDL_Renderer* renderer, TileType type, int col, int row,
                const SDL_FRect& rect, float worldTime) {
    switch (type) {
        case TileType::Grass: {
            setDrawColor(renderer,
                         ((col + row) % 2 == 0) ? kGrassColor : kGrassAltColor);
            SDL_RenderFillRect(renderer, &rect);
            break;
        }
        case TileType::Rock: {
            setDrawColor(renderer, kRockColor);
            SDL_RenderFillRect(renderer, &rect);
            const SDL_FRect highlight{rect.x + 4.0f, rect.y + 4.0f,
                                      rect.w - 10.0f, rect.h - 10.0f};
            setDrawColor(renderer, kRockHighlightColor);
            SDL_RenderFillRect(renderer, &highlight);
            break;
        }
        case TileType::River: {
            setDrawColor(renderer, kRiverColor);
            SDL_RenderFillRect(renderer, &rect);
            constexpr float kFlowSpeed = 24.0f;
            const float phase = (worldTime * kFlowSpeed) + ((col % 2) * 16.0f);
            const float offset1 = std::fmod(phase, static_cast<float>(kTileSize));
            const float offset2 =
                std::fmod(phase + 16.0f, static_cast<float>(kTileSize));

            setDrawColor(renderer, kRiverRippleColor);
            const SDL_FRect ripple1{rect.x + 4.0f, rect.y + offset1,
                                    rect.w - 12.0f, 3.0f};
            SDL_RenderFillRect(renderer, &ripple1);
            const SDL_FRect ripple2{rect.x + 10.0f, rect.y + offset2,
                                    rect.w - 14.0f, 3.0f};
            SDL_RenderFillRect(renderer, &ripple2);
            break;
        }
    }
}

}  // namespace

void renderWorld(SDL_Renderer* renderer, const WorldMap& map, float cameraX,
                 float cameraY, float worldTime) {
    const int startCol = std::max(0, static_cast<int>(cameraX) / kTileSize);
    const int endCol = std::min(
        kMapCols - 1, static_cast<int>(cameraX + kWindowWidth) / kTileSize);
    const int startRow = std::max(0, static_cast<int>(cameraY) / kTileSize);
    const int endRow = std::min(
        kMapRows - 1, static_cast<int>(cameraY + kWindowHeight) / kTileSize);

    for (int r = startRow; r <= endRow; ++r) {
        for (int c = startCol; c <= endCol; ++c) {
            const SDL_FRect tileRect{
                static_cast<float>(c * kTileSize) - cameraX,
                static_cast<float>(r * kTileSize) - cameraY,
                static_cast<float>(kTileSize),
                static_cast<float>(kTileSize),
            };
            renderTile(renderer, map.tileAt(c, r), c, r, tileRect, worldTime);
        }
    }
}

}  // namespace rogue20
