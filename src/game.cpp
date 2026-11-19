//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "game.h"

#include <algorithm>
#include <cstdint>
#include <iostream>

#include "config.h"
#include "hud_renderer.h"
#include "player_renderer.h"
#include "world_renderer.h"

namespace rogue20 {

Game::~Game() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_) {
        SDL_DestroyWindow(window_);
    }
    SDL_Quit();
}

bool Game::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Rogue20", kWindowWidth, kWindowHeight, 0,
                                     &window_, &renderer_)) {
        std::cerr << "SDL_CreateWindowAndRenderer failed: " << SDL_GetError()
                  << '\n';
        return false;
    }

    map_.build();
    player_.spawn();
    return true;
}

void Game::run() {
    bool running = true;
    std::uint64_t lastTicks = SDL_GetTicksNS();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    running = false;
                } else if (event.key.key == SDLK_SPACE && !event.key.repeat) {
                    player_.triggerSwing();
                }
            }
        }

        const std::uint64_t now = SDL_GetTicksNS();
        const float dt =
            static_cast<float>(now - lastTicks) / 1'000'000'000.0f;
        lastTicks = now;

        update(std::min(dt, 0.05f));
        render();
    }
}

void Game::update(float dt) {
    worldTime_ += dt;
    player_.update(dt, map_);
    camera_.update(player_.x, player_.y, player_.size);
}

void Game::render() const {
    SDL_SetRenderDrawColor(renderer_, 20, 20, 20, 255);
    SDL_RenderClear(renderer_);

    const SDL_Rect worldViewport{0, 0, kViewportWidth, kWindowHeight};
    SDL_SetRenderViewport(renderer_, &worldViewport);
    renderWorld(renderer_, map_, camera_.x(), camera_.y(), worldTime_);
    renderPlayer(renderer_, player_, camera_.x(), camera_.y());

    SDL_SetRenderViewport(renderer_, nullptr);
    renderHud(renderer_, player_);

    SDL_RenderPresent(renderer_);
}

}  // namespace rogue20
