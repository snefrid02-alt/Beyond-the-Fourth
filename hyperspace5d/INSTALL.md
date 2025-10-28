# HyperSpace5D - Installation Guide

## System Requirements

### Minimum Requirements
- **OS**: Linux (tested on Arch Linux)
- **CPU**: Dual-core processor (2.0 GHz+)
- **RAM**: 512 MB
- **GPU**: OpenGL 4.5 compatible graphics card
- **Storage**: 50 MB free space

### Recommended Requirements
- **OS**: Arch Linux, Ubuntu 20.04+, Fedora 35+
- **CPU**: Quad-core processor (3.0 GHz+)
- **RAM**: 2 GB
- **GPU**: Modern GPU with OpenGL 4.5+ support
- **Storage**: 100 MB free space

## Installation Methods

### Method 1: Using the Build Script (Recommended)

#### Step 1: Install Dependencies (Arch Linux)
```bash
yay -S base-devel cmake gcc glm sdl2 glew imgui
```

#### For Other Distributions

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential cmake g++ libglm-dev libsdl2-dev libglew-dev
# ImGui may need to be installed manually or built from source
```

**Fedora:**
```bash
sudo dnf install cmake gcc-c++ glm-devel SDL2-devel glew-devel
# ImGui may need to be installed manually or built from source
```

#### Step 2: Extract and Build
```bash
tar -xzf hyperspace5d-1.0.0.tar.gz
cd hyperspace5d-1.0.0
chmod +x build.sh
./build.sh
```

#### Step 3: Run the Game
```bash
cd build
./HyperSpace5D
```

### Method 2: Manual CMake Build

```bash
# Extract the archive
tar -xzf hyperspace5d-1.0.0.tar.gz
cd hyperspace5d-1.0.0

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compile
make -j$(nproc)

# Run
./HyperSpace5D
```

### Method 3: Development Build

For development with debug symbols:

```bash
mkdir -p build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
./HyperSpace5D
```

## Dependency Details

### Required Libraries

| Library | Package Name (Arch) | Purpose |
|---------|---------------------|---------|
| **CMake** | `cmake` | Build system generator |
| **GCC** | `gcc` | C++ compiler with C++20 support |
| **OpenGL** | (system) | Graphics rendering API |
| **GLEW** | `glew` | OpenGL extension loading |
| **SDL2** | `sdl2` | Window management and input |
| **GLM** | `glm` | Mathematics library (header-only) |
| **ImGui** | `imgui` | Debug UI library |

### Installing ImGui

If ImGui is not available in your package manager:

```bash
# Download ImGui
git clone https://github.com/ocornut/imgui.git /tmp/imgui

# Copy to system include directory (may require sudo)
sudo mkdir -p /usr/include/imgui
sudo cp -r /tmp/imgui/* /usr/include/imgui/
```

Alternatively, place ImGui in the project directory:
```bash
cd hyperspace5d-1.0.0
git clone https://github.com/ocornut/imgui.git external/imgui
```

Then update `CMakeLists.txt`:
```cmake
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
```

## Verifying Installation

### Check OpenGL Version
```bash
glxinfo | grep "OpenGL version"
```

Should show OpenGL 4.5 or higher.

### Test Build
After building, verify the executable:
```bash
cd build
file ./HyperSpace5D
ldd ./HyperSpace5D  # Check library dependencies
```

### Run Test
```bash
./HyperSpace5D
```

You should see:
- A window titled "HyperSpace5D - 5D Puzzle Platformer"
- The first level loaded
- Debug UI on the right side
- Controls help on the left side

## Troubleshooting

### CMake Configuration Fails

**Problem**: `CMake Error: Could not find...`

**Solution**: Install missing dependency
```bash
# Check which package provides the missing file
yay -F <missing-file>

# Install the package
yay -S <package-name>
```

### OpenGL Version Error

**Problem**: "OpenGL 4.5 not supported"

**Solution**: Update graphics drivers
```bash
# For Arch Linux with AMD GPU
yay -S mesa vulkan-radeon

# For Arch Linux with NVIDIA GPU
yay -S nvidia nvidia-utils

# For Arch Linux with Intel GPU
yay -S mesa vulkan-intel
```

### Shader Compilation Fails

**Problem**: Shader errors at runtime

**Solution**: Verify shaders directory exists
```bash
cd build
ls -la shaders/
```

If missing:
```bash
cp -r ../shaders .
```

### ImGui Headers Not Found

**Problem**: `fatal error: imgui.h: No such file or directory`

**Solution**: Install ImGui or update CMakeLists.txt path
```bash
# Option 1: Install system-wide
yay -S imgui

# Option 2: Clone to project
git clone https://github.com/ocornut/imgui.git external/imgui
# Update IMGUI_DIR in CMakeLists.txt
```

### Missing SDL2 Headers

**Problem**: `fatal error: SDL2/SDL.h: No such file or directory`

**Solution**: Install SDL2 development packages
```bash
yay -S sdl2
# or
sudo apt install libsdl2-dev
```

### Game Crashes on Startup

**Problem**: Segmentation fault or immediate crash

**Solutions**:
1. Check you're running from the build directory (needs shaders/)
2. Verify OpenGL support: `glxinfo | grep OpenGL`
3. Update graphics drivers
4. Run with debug info:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
gdb ./HyperSpace5D
(gdb) run
(gdb) backtrace  # After crash
```

### Poor Performance

**Problem**: Low FPS or stuttering

**Solutions**:
1. Close unnecessary applications
2. Reduce window resolution (edit main.cpp, recompile)
3. Disable VSync (edit main.cpp: `SDL_GL_SetSwapInterval(0)`)
4. Check GPU usage: `nvidia-smi` or `radeontop`

### Save File Issues

**Problem**: Can't save/load progress

**Solution**: Ensure write permissions
```bash
# Check current directory permissions
ls -la savegame.dat

# If needed, fix permissions
chmod 644 savegame.dat
```

## Uninstallation

### Remove Build Files
```bash
cd hyperspace5d-1.0.0
rm -rf build/
```

### Remove Entire Project
```bash
cd ..
rm -rf hyperspace5d-1.0.0/
rm hyperspace5d-1.0.0.tar.gz
```

### Remove Dependencies (Careful!)
```bash
# Only if you don't need them for other projects
yay -R imgui glew sdl2 glm
```

## Advanced Configuration

### Change Window Resolution

Edit `src/main.cpp`:
```cpp
const int SCREEN_WIDTH = 1920;  // Change this
const int SCREEN_HEIGHT = 1080; // And this
```

Rebuild:
```bash
cd build && make
```

### Disable VSync

Edit `src/main.cpp`:
```cpp
SDL_GL_SetSwapInterval(0);  // Change 1 to 0
```

### Adjust Camera Position

Edit `src/engine/Renderer.hpp`:
```cpp
glm::vec3 cameraPos(0.0f, 5.0f, 20.0f);  // Adjust Z for distance
```

### Modify Game Physics

Edit `src/engine/Player5D.hpp`:
```cpp
float moveSpeed = 5.0f;       // Movement speed
float jumpStrength = 8.0f;    // Jump height
float gravity = 20.0f;        // Gravity strength
```

## Getting Help

### Check Logs
The game outputs debug information to stdout. Run with:
```bash
./HyperSpace5D 2>&1 | tee game.log
```

### Common Error Messages

| Error | Meaning | Solution |
|-------|---------|----------|
| "Failed to initialize SDL" | SDL2 not installed | Install SDL2 |
| "Failed to initialize GLEW" | OpenGL issue | Update GPU drivers |
| "Failed to load shaders" | Shader files missing | Copy shaders/ to build/ |
| "Failed to initialize game" | General init error | Check all dependencies |

### Debug Mode

For detailed debugging:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON
make VERBOSE=1
gdb ./HyperSpace5D
```

## Building Distribution Package

To create a distributable tarball:

```bash
./build.sh
# Creates hyperspace5d-1.0.0.tar.gz
```

The package includes:
- Source code
- Shaders
- Assets
- Build scripts
- Documentation
- Compiled binary (if build succeeds)

---

**Happy gaming in 5 dimensions!** 🚀

For more information, see:
- [README.md](README.md) - General game information
- [ARCHITECTURE.md](ARCHITECTURE.md) - Technical details
- [QUICKSTART.md](QUICKSTART.md) - Quick reference guide
