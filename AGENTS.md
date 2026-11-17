# AGENTS.md

Instructions for AI agents working on **Rogue20**.

## Project Overview

- **Language / Standard**: C++20 (`CMAKE_CXX_STANDARD 20`, `CMAKE_CXX_STANDARD_REQUIRED ON`)
- **Graphics / Windowing**: SDL3 (`find_package(SDL3 REQUIRED CONFIG)`, linked via `SDL3::SDL3`)
- **Build System**: CMake (minimum version `4.4` in `CMakeLists.txt`)
- **Layout**:
  - `CMakeLists.txt` — CMake configuration defining the `Rogue20` executable target.
  - `main.cpp` — Single-file game implementation (constants, tile/player types, `Game` class, and `main()`).
  - `README.md` — Platform setup and build instructions.
  - `build/` and `cmake-build-debug/` — Local build directories (do not commit or treat as source).

## Building & Verifying

Configure and build from the repository root:

```sh
cmake -B build -S .
cmake --build build
```

Run the game binary:

```sh
./build/Rogue20
```

- Always run `cmake --build build` after modifying `main.cpp` or `CMakeLists.txt` to verify the project compiles cleanly.
- There is currently no automated test suite; verify changes by building and, when appropriate, running `./build/Rogue20` (note: running the GUI binary requires a display environment).

## Code Structure (`main.cpp`)

Everything currently lives in `main.cpp` inside an anonymous `namespace` plus `main()`:

- **Configuration constants**: `kWindowWidth` (`960`), `kWindowHeight` (`640`), `kTileSize` (`32`), `kMapCols` (`54`), `kMapRows` (`36`), `kWorldWidth`, `kWorldHeight`, `kCameraMargin` (`160.0f`).
- **World & Tiles**: `TileType` enum and `Color` constants (`kGrassColor`, `kRockColor`, `kRiverColor`, etc.).
- **Player**: `Direction` enum and `Player` struct.
- **Game Loop & Logic**: `Game` class handling SDL3 initialization, input (WASD / Arrow Keys, Esc / quit), world generation, collision/movement, camera scrolling, and rendering.

## Guidelines for Modifying the Game

1. **Preserve C++20 & SDL3 conventions**: Use SDL3 APIs (`SDL3/SDL.h`) and standard C++20 features. Avoid introducing external dependencies unless explicitly requested.
2. **Adding source files**: If splitting `main.cpp` into multiple `.cpp`/`.hpp` files, update `add_executable(Rogue20 ...)` in `CMakeLists.txt` and re-run `cmake -B build -S .` before building.
3. **Constants & Dimensions**: Keep `kWorldWidth` / `kWorldHeight` derived from `kMapCols * kTileSize` and `kMapRows * kTileSize` so viewport/camera clamping stays consistent.
4. **Documentation**: If you change controls, window/world dimensions, or build requirements, update `README.md` to match.
