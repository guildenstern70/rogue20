# Rogue20

**Rogue20** is a 2D roguelite game testbed written in **C++20** using **SDL3**.

## Features

- **2D Tile World**: Grass, solid rock formations, and an animated north-to-south flowing river with shallow crossings.
- **Animated Warrior**: A warrior with a shield and sword featuring a 4-direction walking animation (North, South, East, West).
- **Controls**: Move with **WASD** or **Arrow Keys**; press **Esc** or close the window to quit.
- **Scrolling Viewport**: A `960x640` window that follows the player across a larger (`1728x1152`) level when approaching the viewport edges.

## Prerequisites

- A **C++20** compatible compiler (Clang, GCC, or MSVC)
- **CMake** (4.4 or higher, as specified in `CMakeLists.txt`)
- **SDL3** development libraries

---

## Setup & Build

### macOS

1. Install CMake and SDL3 using [Homebrew](https://brew.sh/):
   ```sh
   brew install cmake sdl3
   ```
2. Configure and build:
   ```sh
   cmake -B build -S .
   cmake --build build
   ```
3. Run the game:
   ```sh
   ./build/Rogue20
   ```

### Linux (Ubuntu / Debian / Fedora)

1. Install build tools and CMake:
   - **Ubuntu / Debian**:
     ```sh
     sudo apt update
     sudo apt install build-essential cmake git
     ```
   - **Fedora**:
     ```sh
     sudo dnf install gcc-c++ cmake git
     ```
2. Install **SDL3** (via your distribution's package manager if available, or build from source):
   ```sh
   git clone https://github.com/libsdl-org/SDL.git
   cd SDL
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   cmake --build build
   sudo cmake --install build
   cd ..
   ```
3. Configure and build Rogue20:
   ```sh
   cmake -B build -S .
   cmake --build build
   ```
4. Run the game:
   ```sh
   ./build/Rogue20
   ```

### Windows

1. Install **Visual Studio 2022** (with the *Desktop development with C++* workload) and **CMake** (or use the CMake bundled with Visual Studio).
2. Install **SDL3** using [vcpkg](https://vcpkg.io/):
   ```powershell
   vcpkg install sdl3:x64-windows
   ```
3. Configure and build (replace `<path-to-vcpkg>` with your vcpkg installation path):
   ```powershell
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Release
   ```
4. Run the game:
   ```powershell
   .\build\Release\Rogue20.exe
   ```
