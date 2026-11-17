//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//

#pragma once

#include <cstdint>

namespace rogue20 {

constexpr int kWindowWidth = 960;
constexpr int kWindowHeight = 640;
constexpr int kTileSize = 32;
constexpr int kMapCols = 54;   // ~1.8x width, ~3.2x total area of viewport
constexpr int kMapRows = 36;   // ~1.8x height
constexpr int kWorldWidth = kMapCols * kTileSize;
constexpr int kWorldHeight = kMapRows * kTileSize;
constexpr float kCameraMargin = 160.0f;

struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a = 255;
};

constexpr Color kGrassColor{74, 148, 68};
constexpr Color kGrassAltColor{68, 138, 62};
constexpr Color kRockColor{120, 124, 130};
constexpr Color kRockHighlightColor{148, 152, 158};
constexpr Color kRiverColor{46, 118, 196};
constexpr Color kRiverRippleColor{76, 148, 222};
constexpr Color kPlayerColor{235, 196, 64};
constexpr Color kPlayerOutlineColor{40, 32, 16};

}  // namespace rogue20
