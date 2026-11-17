//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <cstdint>

#include "config.h"

namespace rogue20 {

enum class TileType : std::uint8_t {
    Grass,
    Rock,
    River,
};

class WorldMap {
public:
    void build();
    TileType tileAt(int col, int row) const;
    void setTile(int col, int row, TileType type);
    bool isSolid(TileType type) const;
    bool collidesWithRect(float x, float y, float size) const;

private:
    std::array<TileType, kMapCols * kMapRows> tiles_{};
};

}  // namespace rogue20
