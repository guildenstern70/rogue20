//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//

#include "hud_renderer.h"

#include <algorithm>
#include <array>
#include <utility>

#include "config.h"

namespace rogue20 {

namespace {

void setDrawColor(SDL_Renderer* renderer, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void drawDivider(SDL_Renderer* renderer, float x, float y, float width) {
    setDrawColor(renderer, kSidebarBorderColor);
    const SDL_FRect line{x, y, width, 1.0f};
    SDL_RenderFillRect(renderer, &line);
}

}  // namespace

void renderHud(SDL_Renderer* renderer, const Player& player) {
    const float panelX = static_cast<float>(kViewportWidth);
    const float panelW = static_cast<float>(kSidebarWidth);
    const float panelH = static_cast<float>(kWindowHeight);

    const SDL_FRect bgRect{panelX, 0.0f, panelW, panelH};
    setDrawColor(renderer, kSidebarBgColor);
    SDL_RenderFillRect(renderer, &bgRect);

    const SDL_FRect borderRect{panelX, 0.0f, 2.0f, panelH};
    setDrawColor(renderer, kSidebarBorderColor);
    SDL_RenderFillRect(renderer, &borderRect);

    constexpr float kPadding = 20.0f;
    constexpr float kTextScale = 2.0f;
    const float contentX = panelX + kPadding;
    const float contentW = panelW - 2.0f * kPadding;
    const float scaledX = contentX / kTextScale;

    SDL_SetRenderScale(renderer, kTextScale, kTextScale);

    // First line: Rogue 20
    setDrawColor(renderer, kTextTitleColor);
    SDL_RenderDebugText(renderer, scaledX, 24.0f / kTextScale, "Rogue 20");

    // Character name
    setDrawColor(renderer, kTextPrimaryColor);
    SDL_RenderDebugText(renderer, scaledX, 68.0f / kTextScale,
                        player.name.c_str());

    // Core attributes
    const std::array<std::pair<const char*, int>, 4> stats{{
        {"ST", player.st},
        {"DX", player.dx},
        {"IQ", player.iq},
        {"HT", player.ht},
    }};

    float statY = 112.0f;
    constexpr float kStatStep = 28.0f;
    for (const auto& [label, value] : stats) {
        setDrawColor(renderer, kTextMutedColor);
        SDL_RenderDebugText(renderer, scaledX, statY / kTextScale, label);
        setDrawColor(renderer, kTextPrimaryColor);
        SDL_RenderDebugTextFormat(renderer, (contentX + 64.0f) / kTextScale,
                                  statY / kTextScale, "%2d", value);
        statY += kStatStep;
    }

    // Current HP / Total HP
    constexpr float kHpY = 248.0f;
    setDrawColor(renderer, kTextMutedColor);
    SDL_RenderDebugText(renderer, scaledX, kHpY / kTextScale, "HP");
    setDrawColor(renderer, kTextPrimaryColor);
    SDL_RenderDebugTextFormat(renderer, (contentX + 48.0f) / kTextScale,
                              kHpY / kTextScale, "%d / %d", player.hp,
                              player.maxHp);

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    drawDivider(renderer, contentX, 52.0f, contentW);
    drawDivider(renderer, contentX, 230.0f, contentW);

    // HP bar below HP text
    const float hpRatio =
        (player.maxHp > 0)
            ? std::clamp(static_cast<float>(player.hp) /
                             static_cast<float>(player.maxHp),
                         0.0f, 1.0f)
            : 0.0f;
    const SDL_FRect hpBarBg{contentX, 276.0f, contentW, 10.0f};
    setDrawColor(renderer, kHpBarBgColor);
    SDL_RenderFillRect(renderer, &hpBarBg);

    const SDL_FRect hpBarFill{contentX, 276.0f, contentW * hpRatio, 10.0f};
    setDrawColor(renderer, kHpBarFillColor);
    SDL_RenderFillRect(renderer, &hpBarFill);
}

}  // namespace rogue20
