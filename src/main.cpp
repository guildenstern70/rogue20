//
// The Rogue 20 Project
// (C) 2026 Alessio Saltarin
//
//  This software is licensed unser ISC
//  (see LICENSE)
//
#include "game.h"

int main() {
    rogue20::Game game;
    if (!game.init()) {
        return 1;
    }
    game.run();
    return 0;
}
