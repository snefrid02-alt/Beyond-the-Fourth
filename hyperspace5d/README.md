# HyperSpace5D - 5D Puzzle Platformer

A mind-bending puzzle platformer that takes place in **five spatial dimensions** (X, Y, Z, W, V). Inspired by Miegakure but with one additional spatial dimension, HyperSpace5D challenges players to navigate impossible geometries by rotating their view through different 3D slices of 5D space.

## Game Concept

In our 3D world, we can only perceive three spatial dimensions at once. HyperSpace5D extends this concept to **five dimensions**. As the player, you exist in full 5D space, but you can only see 3 dimensions at a time. By rotating your view to look at different 3D "slices" of the 5D world, objects appear, disappear, and paths emerge that seemed impossible moments ago.

### Core Mechanics

- **5D Movement**: Move through five spatial dimensions (X, Y, Z, W, V)
- **Dimension Rotation**: Rotate your view to see different 3D slices of the 5D world
- **Platforming**: Jump, dash, and wall-slide through impossible geometries
- **Puzzle Solving**: Use dimension rotation to reveal hidden platforms, bypass obstacles, and find paths to the goal

### Visual Feedback

Objects in the game provide visual cues about their position in 5D space:
- **Opacity**: Objects further away in hidden dimensions appear more transparent
- **Scale**: Objects shrink based on their distance in hidden dimensions
- **Color Tint**: Warm/cool colors indicate position in hidden dimensions (W and V)

## Installation & Dependencies

### For Arch Linux

Install all required dependencies using `yay`:

```bash
yay -S base-devel cmake gcc glm sdl2 glew imgui
```

### Dependency Details

- **base-devel**: Essential build tools (make, gcc, etc.)
- **cmake**: Build system generator (3.15+)
- **gcc**: C++ compiler with C++20 support
- **glm**: OpenGL Mathematics library for vector/matrix operations
- **sdl2**: Simple DirectMedia Layer for windowing and input
- **glew**: OpenGL Extension Wrangler for loading OpenGL extensions
- **imgui**: Immediate Mode GUI for debug interface

## Building the Game

### Standard Build

```bash
cd hyperspace5d
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

### Run the Game

```bash
./HyperSpace5D
```

The game will look for `shaders/` and `assets/` directories in the current working directory. Make sure to run from the build directory where these have been copied.

### Alternative: Out-of-Source Build

```bash
mkdir -p build
cd build
cmake ../hyperspace5d
make -j$(nproc)
./HyperSpace5D
```

## Controls

### Movement
- **W/A/S/D**: Move in the current 3D slice
- **Space**: Jump (can wall-jump when touching walls)
- **Left Shift**: Dash in the direction of movement

### Dimension Control

#### Quick Rotation
- **Q**: Rotate to XYW view (swap Z with W)
- **E**: Rotate to XYV view (swap Z with V)
- **R**: Return to XYZ view (standard 3D)

#### Direct Dimension Views (Number Keys)
- **1**: XYZ view (standard 3D space)
- **2**: XYW view (4th dimension W replaces Z)
- **3**: XYV view (5th dimension V replaces Z)
- **4**: XZW view
- **5**: XZV view
- **6**: YZW view
- **7**: YZV view
- **8**: XWV view
- **9**: YWV view
- **0**: ZWV view

### Level Navigation
- **ESC**: Restart current level
- **F1**: Previous level
- **F2**: Next level

### UI Controls
- **F3**: Toggle debug information panel
- **F4**: Toggle help/controls panel

## Levels

HyperSpace5D features **11 progressively challenging levels** that teach you to master five-dimensional navigation!

### Early Game: Foundation (⭐☆☆)

#### Level 1: Introduction to 5D Space
Learn the basic mechanics of 5D movement and dimension rotation. Features a platform that only exists in certain dimensional views.
**Key Concept**: Objects can be invisible in one 3D slice but visible in another.

#### Level 2: 5D Platforming
Master timing and precision with platforms that move through different dimensions.
**Key Concept**: Objects moving in hidden dimensions periodically intersect with your current view.

#### Level 3: Hypercube Maze
Navigate a complex maze where walls exist in some dimensional views but not others.
**Key Concept**: Strategic dimension rotation reveals different paths through the same space.

### Mid Game: Advanced Puzzles (⭐⭐☆)

#### Level 4: Pentacube Maze
Navigate a 5D hypercube where each 3D slice shows a different maze section. Requires using all 10 dimensional views!
**Key Concept**: Comprehensive dimensional rotation mastery.

#### Level 5: Dimensional Bridges
Bridges that only exist when viewing specific dimensional pairs. Must switch views mid-jump!
**Key Concept**: Trust invisible platforms and time your dimension switches.

#### Level 6: Hyperspace Teleportation
Portals connect distant points in 5D space. What looks far in XYZ might be adjacent in XWV view.
**Key Concept**: Non-Euclidean spatial relationships and 5D topology.

#### Level 7: Phase Objects
Objects occupy different hypervolumes - can only interact with them from certain dimensional perspectives.
**Key Concept**: Understanding 5D occupancy and hypervolume intersection.

### Late Game: Mastery Required (⭐⭐⭐)

#### Level 8: 5D Rotation Puzzles
Keys and switches require specific dimensional rotation sequences to activate. Like combination locks in 5D!
**Key Concept**: Sequential dimensional thinking and precise control.

#### Level 9: Temporal Echoes
Objects leave "trails" in the V-dimension that persist and can be used as platforms.
**Key Concept**: Creative use of the 5th dimension as pseudo-temporal.

#### Level 10: Hypersurface Walking
Walk on 4D hypersurfaces embedded in 5D space. The surface appears different from each 3D angle.
**Key Concept**: Advanced topology and hypersurface intuition.

### Boss Level: Ultimate Challenge (⭐⭐⭐⭐⭐)

#### Level 11: The Pentarch
Face **The Pentarch** - a 5D entity with 5 cores, each vulnerable from only one specific dimensional view! Master of all five dimensions, it attacks with 5D projectiles, creates hyperwalls, and manipulates the arena geometry. Defeat all 5 cores while dodging attacks in a dynamically changing 5D battlefield.
**Key Concept**: Apply ALL skills learned under extreme pressure!

**For detailed walkthrough and puzzle solutions**, see [LEVEL_DESIGN.md](LEVEL_DESIGN.md)

## Mathematical Explanation

### 5D Space Representation

A point in 5D space is represented by five coordinates: **(x, y, z, w, v)**

- **X, Y, Z**: Standard 3D spatial dimensions
- **W**: Fourth spatial dimension (perpendicular to X, Y, Z)
- **V**: Fifth spatial dimension (perpendicular to X, Y, Z, W)

### Dimension Projection

At any time, you view three of these five dimensions. The projection process:

1. **Apply 5D Rotation Matrix**: Orient the 5D space
2. **Extract 3 Visible Dimensions**: Select which 3 coordinates to display
3. **Calculate Hidden Depth**: Measure distance in the 2 hidden dimensions
4. **Apply Visual Effects**: Modify opacity, scale, and color based on hidden depth

### 5D Rotations

In 5D space, rotations occur in **2D planes** embedded in the 5D space. There are **10 possible rotation planes**:

- **3D planes**: XY, XZ, XW, XV, YZ, YW, YV, ZW, ZV, WV

A 5D rotation matrix is represented as a 5×5 matrix. Simple rotations in a single plane are defined by:

```
R(i,j,θ) = rotation by angle θ in the plane spanned by axes i and j
```

The game uses these planar rotations to smoothly transition between different dimensional views.

### Collision Detection in 5D

Collision detection uses **5D Axis-Aligned Bounding Boxes (AABB)**. Two objects collide if they overlap in **all five dimensions** simultaneously:

```
For each dimension d ∈ {X, Y, Z, W, V}:
    if (max₁[d] < min₂[d]) or (max₂[d] < min₁[d]):
        return NO_COLLISION
return COLLISION
```

This means an object can avoid collision by moving in dimensions you can't currently see!

## Save System

The game automatically saves your progress to `savegame.dat` in the current directory. This includes:
- Current level
- Highest level reached
- Total play time

## Architecture

For detailed technical information about the implementation, see [ARCHITECTURE.md](ARCHITECTURE.md).

## Project Structure

```
hyperspace5d/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── ARCHITECTURE.md         # Technical architecture documentation
├── build.sh               # Build and packaging script
├── .gitignore             # Git ignore rules
├── src/
│   ├── main.cpp           # Application entry point
│   ├── core/              # Core 5D mathematics
│   │   ├── Vec5D.hpp      # 5D vector class
│   │   ├── Matrix5D.hpp   # 5D transformation matrices
│   │   ├── DimensionState.hpp    # Dimension view management
│   │   └── Projection5D.hpp      # 5D→3D projection
│   ├── engine/            # Game engine
│   │   ├── GameObject5D.hpp      # Base game object class
│   │   ├── Player5D.hpp   # Player controller
│   │   ├── Physics5D.hpp  # 5D physics engine
│   │   └── Renderer.hpp   # OpenGL rendering
│   └── game/              # Game logic
│       ├── Game.hpp       # Main game state
│       └── Level.hpp      # Level definitions
├── shaders/
│   ├── vertex.glsl        # Vertex shader
│   └── fragment.glsl      # Fragment shader
└── assets/
    ├── levels/            # Level data files
    └── textures/          # Texture resources
```

## Building a Release Package

To create a distributable tar.gz archive:

```bash
./build.sh
```

This will:
1. Create a clean build
2. Compile the game
3. Package source code, assets, and documentation
4. Generate `hyperspace5d-1.0.0.tar.gz`

## Troubleshooting

### Shader Compilation Errors
- Ensure you're using OpenGL 4.5 or later
- Check that shader files are in the correct location (`shaders/` directory)
- Verify your GPU supports the required OpenGL version

### ImGui Not Found
- If ImGui headers aren't found, you may need to clone ImGui manually:
```bash
git clone https://github.com/ocornut/imgui.git /tmp/imgui
sudo cp -r /tmp/imgui /usr/include/
```
- Then adjust `IMGUI_DIR` in CMakeLists.txt if needed

### Performance Issues
- Try reducing window resolution in the source code (SCREEN_WIDTH/SCREEN_HEIGHT)
- Disable VSync if needed (SDL_GL_SetSwapInterval(0))
- Check GPU drivers are up to date

## Credits

**Concept Inspired By**: Miegakure by Marc Ten Bosch (4D puzzle platformer)

**Developed For**: Educational demonstration of higher-dimensional geometry

**Technologies**: C++20, OpenGL 4.5, SDL2, GLM, GLEW, ImGui

## License

This is free and unencumbered software released into the **public domain** under [The Unlicense](http://unlicense.org/).

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

See the [LICENSE](LICENSE) file for complete details.

## Current Features (v2.0)

✓ **11 Progressive Levels** including epic boss fight  
✓ **The Pentarch Boss** - 5D combat with dynamic arena  
✓ **Advanced Puzzle Mechanics**:
  - Pentacube mazes spanning all dimensional views
  - Dimensional bridges that phase in/out
  - Hyperspace portals and non-Euclidean connections
  - Phase objects with selective interaction
  - 5D rotation puzzles and combination locks
  - Temporal echoes in the V-dimension
  - 4D hypersurface walking
  
✓ **Complete Boss Fight System**:
  - 5 cores vulnerable from different views
  - 4 escalating phases
  - 5D projectiles and hyperwalls
  - Dynamic geometry manipulation

## Future Enhancements

Potential additions for future versions:
- More complex 5D shapes (hyperspheres, hyperprisms)
- Additional boss enemies with unique 5D abilities
- Enemies with 5D AI navigation
- Level editor with 5D object placement
- Multiplayer with synchronized dimensional views
- VR support for enhanced spatial perception
- Custom shader effects for dimensional transitions
- Sound design that reflects hidden dimensions
- Procedurally generated 5D mazes
- Speedrun mode and leaderboards

---

**Have fun exploring the fifth dimension!** 🚀✨
