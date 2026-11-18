//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//


#include "world_map.h"

#include <utility>
#include <vector>

namespace rogue20 {

void WorldMap::build() {
    tiles_.fill(TileType::Grass);

    for (int c = 0; c < kMapCols; ++c) {
        setTile(c, 0, TileType::Rock);
        setTile(c, kMapRows - 1, TileType::Rock);
    }
    for (int r = 0; r < kMapRows; ++r) {
        setTile(0, r, TileType::Rock);
        setTile(kMapCols - 1, r, TileType::Rock);
    }

    int riverCol = 28;
    for (int r = 1; r < kMapRows - 1; ++r) {
        if (r == 6 || r == 14 || r == 25) {
            riverCol += 1;
        } else if (r == 10 || r == 20 || r == 30) {
            riverCol -= 1;
        }
        if (r == 9 || r == 10 || r == 24 || r == 25) {
            continue;
        }
        setTile(riverCol, r, TileType::River);
        setTile(riverCol + 1, r, TileType::River);
    }

    const std::vector<std::pair<int, int>> rocks = {
        {5, 4},   {6, 4},   {5, 5},   {11, 3},  {11, 4},  {12, 4},
        {8, 12},  {9, 12},  {9, 13},  {14, 15}, {15, 15}, {15, 16},
        {24, 5},  {25, 5},  {25, 6},  {23, 14}, {24, 14}, {23, 15},
        {36, 7},  {37, 7},  {37, 8},  {42, 12}, {43, 12}, {42, 13},
        {12, 24}, {13, 24}, {13, 25}, {20, 29}, {21, 29}, {20, 30},
        {38, 22}, {39, 22}, {39, 23}, {45, 28}, {46, 28}, {45, 29},
    };
    for (const auto& [c, r] : rocks) {
        setTile(c, r, TileType::Rock);
    }
}

TileType WorldMap::tileAt(int col, int row) const {
    if (col < 0 || col >= kMapCols || row < 0 || row >= kMapRows) {
        return TileType::Rock;
    }
    return tiles_[row * kMapCols + col];
}

void WorldMap::setTile(int col, int row, TileType type) {
    if (col >= 0 && col < kMapCols && row >= 0 && row < kMapRows) {
        tiles_[row * kMapCols + col] = type;
    }
}

bool WorldMap::isSolid(const TileType type) {
    return type == TileType::Rock || type == TileType::River;
}

bool WorldMap::collidesWithRect(float x, float y, float size) const {
    const int left = static_cast<int>(x) / kTileSize;
    const int right = static_cast<int>(x + size - 0.01f) / kTileSize;
    const int top = static_cast<int>(y) / kTileSize;
    const int bottom = static_cast<int>(y + size - 0.01f) / kTileSize;

    for (int r = top; r <= bottom; ++r) {
        for (int c = left; c <= right; ++c) {
            if (isSolid(tileAt(c, r))) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace rogue20
