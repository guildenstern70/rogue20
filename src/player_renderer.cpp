//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "player_renderer.h"

#include <algorithm>
#include <cmath>
#include <numbers>

#include "config.h"

namespace rogue20 {

namespace {

constexpr Color kShieldRim{155, 160, 170};
constexpr Color kShieldWood{132, 82, 42};
constexpr Color kSwordBlade{215, 222, 232};
constexpr Color kSwordHilt{212, 170, 56};

void fillRect(SDL_Renderer* renderer, float x, float y, float w, float h,
              Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    const SDL_FRect rect{x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FColor toFColor(Color c, float alphaScale = 1.0f) {
    return {
        static_cast<float>(c.r) / 255.0f,
        static_cast<float>(c.g) / 255.0f,
        static_cast<float>(c.b) / 255.0f,
        (static_cast<float>(c.a) / 255.0f) * alphaScale,
    };
}

void fillRotatedRect(SDL_Renderer* renderer, float cx, float cy,
                     float offsetAlongDir, float length, float thickness,
                     float angle, Color c) {
    const float cosA = std::cos(angle);
    const float sinA = std::sin(angle);
    const float nx = -sinA;
    const float ny = cosA;
    const float halfT = thickness * 0.5f;

    const float x0 = cx + cosA * offsetAlongDir;
    const float y0 = cy + sinA * offsetAlongDir;
    const float x1 = cx + cosA * (offsetAlongDir + length);
    const float y1 = cy + sinA * (offsetAlongDir + length);

    const SDL_FColor fc = toFColor(c);
    const SDL_Vertex vertices[4] = {
        {{x0 + nx * halfT, y0 + ny * halfT}, fc, {0.0f, 0.0f}},
        {{x1 + nx * halfT, y1 + ny * halfT}, fc, {0.0f, 0.0f}},
        {{x1 - nx * halfT, y1 - ny * halfT}, fc, {0.0f, 0.0f}},
        {{x0 - nx * halfT, y0 - ny * halfT}, fc, {0.0f, 0.0f}},
    };
    constexpr int kIndices[6] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer, nullptr, vertices, 4, kIndices, 6);
}

void renderSlashArc(SDL_Renderer* renderer, float cx, float cy,
                    float startAngle, float endAngle, float innerR,
                    float outerR, float maxAlpha) {
    if (endAngle <= startAngle || maxAlpha <= 0.0f) {
        return;
    }

    constexpr int kSegments = 10;
    constexpr Color kSlashColor{235, 242, 255};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int i = 0; i < kSegments; ++i) {
        const float u0 = static_cast<float>(i) / static_cast<float>(kSegments);
        const float u1 =
            static_cast<float>(i + 1) / static_cast<float>(kSegments);
        const float a0 = startAngle + (endAngle - startAngle) * u0;
        const float a1 = startAngle + (endAngle - startAngle) * u1;

        const SDL_FColor c0 = toFColor(kSlashColor, maxAlpha * u0);
        const SDL_FColor c1 = toFColor(kSlashColor, maxAlpha * u1);

        const float cos0 = std::cos(a0);
        const float sin0 = std::sin(a0);
        const float cos1 = std::cos(a1);
        const float sin1 = std::sin(a1);

        const SDL_Vertex vertices[4] = {
            {{cx + cos0 * innerR, cy + sin0 * innerR}, c0, {0.0f, 0.0f}},
            {{cx + cos0 * outerR, cy + sin0 * outerR}, c0, {0.0f, 0.0f}},
            {{cx + cos1 * outerR, cy + sin1 * outerR}, c1, {0.0f, 0.0f}},
            {{cx + cos1 * innerR, cy + sin1 * innerR}, c1, {0.0f, 0.0f}},
        };
        constexpr int kIndices[6] = {0, 1, 2, 0, 2, 3};
        SDL_RenderGeometry(renderer, nullptr, vertices, 4, kIndices, 6);
    }
}

float facingBaseAngle(Direction facing) {
    constexpr float kPi = std::numbers::pi_v<float>;
    switch (facing) {
        case Direction::East:
            return 0.0f;
        case Direction::South:
            return kPi * 0.5f;
        case Direction::West:
            return kPi;
        case Direction::North:
            return -kPi * 0.5f;
    }
    return 0.0f;
}

void renderSwordSwing(SDL_Renderer* renderer, float px, float py, float bobY,
                      const Player& player) {
    const float t =
        std::clamp(player.swingTime / Player::kSwingDuration, 0.0f, 1.0f);
    const float inv = 1.0f - t;
    const float eased = 1.0f - inv * inv * inv;

    const float baseAngle = facingBaseAngle(player.facing);
    constexpr float kHalfArc = 1.25f;
    const float startAngle = baseAngle - kHalfArc;
    const float endAngle = baseAngle + kHalfArc;
    const float angle = startAngle + (endAngle - startAngle) * eased;

    const float pivotX = px + player.size * 0.5f + std::cos(baseAngle) * 4.0f;
    const float pivotY =
        py + player.size * 0.5f + bobY + std::sin(baseAngle) * 4.0f;

    const float trailStart = std::max(startAngle, angle - 1.15f);
    const float slashAlpha = (1.0f - t * t) * 0.65f;
    renderSlashArc(renderer, pivotX, pivotY, trailStart, angle, 11.0f, 23.0f,
                   slashAlpha);

    fillRotatedRect(renderer, pivotX, pivotY, 2.0f, 4.5f, 2.5f, angle,
                    kSwordHilt);
    fillRotatedRect(renderer, pivotX, pivotY, 6.0f, 2.5f, 7.0f, angle,
                    kSwordHilt);
    fillRotatedRect(renderer, pivotX, pivotY, 8.5f, 14.5f, 3.5f, angle,
                    kSwordBlade);
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
                     float armSwing, Direction facing, bool drawIdleSword) {
    const bool shieldOnRight =
        (facing == Direction::East || facing == Direction::South);
    const float shieldX = shieldOnRight ? (px + 15.0f) : (px - 1.0f);
    const float shieldY = py + 8.0f + bobY - armSwing * 0.5f;
    fillRect(renderer, shieldX, shieldY, 8.0f, 10.0f, kShieldRim);
    fillRect(renderer, shieldX + 1.5f, shieldY + 1.5f, 5.0f, 7.0f, kShieldWood);

    if (drawIdleSword) {
        const float swordX = shieldOnRight ? (px - 2.0f) : (px + 18.0f);
        const float swordY = py + 9.0f + bobY + armSwing;
        fillRect(renderer, swordX, swordY + 2.0f, 6.0f, 2.5f, kSwordHilt);
        fillRect(renderer, swordX + (shieldOnRight ? 1.0f : 2.0f),
                 swordY - 8.0f, 3.0f, 10.0f, kSwordBlade);
    }
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

    if (player.isSwinging && player.facing == Direction::North) {
        renderSwordSwing(renderer, px, py, bobY, player);
    }

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
    renderEquipment(renderer, px, py, bobY, armSwing, player.facing,
                    !player.isSwinging);

    if (player.isSwinging && player.facing != Direction::North) {
        renderSwordSwing(renderer, px, py, bobY, player);
    }
}

}  // namespace rogue20
