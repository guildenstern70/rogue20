//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "player_renderer.h"

#include "config.h"

namespace rogue20 {

namespace {

void fillRect(SDL_Renderer* renderer, float x, float y, float w, float h,
              Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    const SDL_FRect rect{x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void renderHead(SDL_Renderer* renderer, float px, float py, float bobY,
                Direction facing) {
    constexpr Color kSkinColor{230, 188, 150};
    constexpr Color kHelmetColor{165, 172, 182};
    constexpr Color kPlumeColor{205, 58, 58};
    constexpr Color kEyeColor{32, 32, 36};

    switch (facing) {
        case Direction::North:
            fillRect(renderer, px + 5.0f, py - 1.0f + bobY, 12.0f, 10.0f,
                     kHelmetColor);
            fillRect(renderer, px + 9.0f, py - 3.0f + bobY, 4.0f, 3.0f,
                     kPlumeColor);
            break;
        case Direction::South:
            fillRect(renderer, px + 6.0f, py + 1.0f + bobY, 10.0f, 8.0f,
                     kSkinColor);
            fillRect(renderer, px + 8.0f, py + 5.0f + bobY, 2.0f, 2.0f,
                     kEyeColor);
            fillRect(renderer, px + 12.0f, py + 5.0f + bobY, 2.0f, 2.0f,
                     kEyeColor);
            fillRect(renderer, px + 5.0f, py - 1.0f + bobY, 12.0f, 5.0f,
                     kHelmetColor);
            fillRect(renderer, px + 9.0f, py - 3.0f + bobY, 4.0f, 2.0f,
                     kPlumeColor);
            break;
        case Direction::East:
            fillRect(renderer, px + 6.0f, py + 1.0f + bobY, 10.0f, 8.0f,
                     kSkinColor);
            fillRect(renderer, px + 13.0f, py + 5.0f + bobY, 2.0f, 2.0f,
                     kEyeColor);
            fillRect(renderer, px + 5.0f, py - 1.0f + bobY, 12.0f, 5.0f,
                     kHelmetColor);
            fillRect(renderer, px + 7.0f, py - 3.0f + bobY, 4.0f, 2.0f,
                     kPlumeColor);
            break;
        case Direction::West:
            fillRect(renderer, px + 6.0f, py + 1.0f + bobY, 10.0f, 8.0f,
                     kSkinColor);
            fillRect(renderer, px + 7.0f, py + 5.0f + bobY, 2.0f, 2.0f,
                     kEyeColor);
            fillRect(renderer, px + 5.0f, py - 1.0f + bobY, 12.0f, 5.0f,
                     kHelmetColor);
            fillRect(renderer, px + 11.0f, py - 3.0f + bobY, 4.0f, 2.0f,
                     kPlumeColor);
            break;
    }
}

void renderEquipment(SDL_Renderer* renderer, float px, float py, float bobY,
                     float armSwing, Direction facing) {
    constexpr Color kShieldRim{155, 160, 170};
    constexpr Color kShieldWood{132, 82, 42};
    constexpr Color kSwordBlade{215, 222, 232};
    constexpr Color kSwordHilt{212, 170, 56};

    const bool shieldOnRight =
        (facing == Direction::East || facing == Direction::South);
    const float shieldX = shieldOnRight ? (px + 15.0f) : (px - 1.0f);
    const float shieldY = py + 8.0f + bobY - armSwing * 0.5f;
    fillRect(renderer, shieldX, shieldY, 8.0f, 10.0f, kShieldRim);
    fillRect(renderer, shieldX + 1.5f, shieldY + 1.5f, 5.0f, 7.0f, kShieldWood);

    const float swordX = shieldOnRight ? (px - 2.0f) : (px + 18.0f);
    const float swordY = py + 9.0f + bobY + armSwing;
    fillRect(renderer, swordX, swordY + 2.0f, 6.0f, 2.5f, kSwordHilt);
    fillRect(renderer, swordX + (shieldOnRight ? 1.0f : 2.0f), swordY - 8.0f,
             3.0f, 10.0f, kSwordBlade);
}

}  // namespace

void renderPlayer(SDL_Renderer* renderer, const Player& player, float cameraX,
                  float cameraY) {
    const float px = player.x - cameraX;
    const float py = player.y - cameraY;
    const int frame =
        player.isMoving ? (static_cast<int>(player.animTime * 8.0f) % 4) : 0;
    const float bobY = (frame == 1 || frame == 3) ? -1.5f : 0.0f;
    const float leftLeg = (frame == 1) ? -2.5f : (frame == 3 ? 1.5f : 0.0f);
    const float rightLeg = (frame == 3) ? -2.5f : (frame == 1 ? 1.5f : 0.0f);
    const float armSwing = (frame == 1) ? 1.5f : (frame == 3 ? -1.5f : 0.0f);

    fillRect(renderer, px + 2.0f, py + player.size - 2.0f, player.size - 4.0f,
             4.0f, {20, 40, 20, 140});
    fillRect(renderer, px + 5.0f, py + 16.0f + leftLeg, 5.0f, 6.0f,
             {78, 52, 34});
    fillRect(renderer, px + 12.0f, py + 16.0f + rightLeg, 5.0f, 6.0f,
             {78, 52, 34});
    fillRect(renderer, px + 4.0f, py + 8.0f + bobY, 14.0f, 10.0f,
             {70, 110, 175});
    fillRect(renderer, px + 4.0f, py + 15.0f + bobY, 14.0f, 2.0f,
             {110, 72, 38});

    renderHead(renderer, px, py, bobY, player.facing);
    renderEquipment(renderer, px, py, bobY, armSwing, player.facing);
}

}  // namespace rogue20
