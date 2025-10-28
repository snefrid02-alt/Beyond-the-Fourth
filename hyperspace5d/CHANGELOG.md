/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

# HyperSpace5D - Changelog

## Version 2.0.0 - "The Pentarch Update" (2025-10-28)

### 🎮 Major Content Addition
- **Added 8 new levels** (total now 11 levels!)
  - Level 4: Pentacube Maze
  - Level 5: Dimensional Bridges
  - Level 6: Hyperspace Teleportation
  - Level 7: Phase Objects
  - Level 8: 5D Rotation Puzzles
  - Level 9: Temporal Echoes
  - Level 10: Hypersurface Walking
  - Level 11: The Pentarch (Epic Boss Fight!)

### 👾 Boss Battle System
- **The Pentarch**: Ultimate 5D boss enemy
  - 5 cores, each vulnerable from one dimensional view
  - 4 escalating phases with increasing difficulty
  - 5D projectile attacks
  - Hyperwall obstacles
  - Dynamic arena geometry manipulation
  - Victory rewards and statistics

### 🧩 New Puzzle Mechanics
- **Pentacube Maze**: Full hypercube navigation requiring all 10 views
- **Dimensional Bridges**: Platforms that phase in/out based on view
- **Hyperspace Portals**: Non-Euclidean connections through 5D space
- **Phase Objects**: Selective interaction based on hypervolume overlap
- **Rotation Locks**: Combination puzzles requiring specific view sequences
- **Temporal Echoes**: V-dimension trails that persist as platforms
- **Hypersurface Walking**: 4D surfaces embedded in 5D space

### 📚 Documentation
- Added comprehensive **LEVEL_DESIGN.md** (24,000+ words)
  - Detailed walkthrough for all 11 levels
  - Intended solution paths
  - Teaching objectives for each puzzle
  - Boss strategy guide
  - Design philosophy and principles
- Added **CHANGELOG.md** (this file!)

### ⚖️ License Change
- **Changed to The Unlicense (Public Domain)**
  - Now completely free for any use
  - No restrictions whatsoever
  - Added LICENSE file with full text
  - Updated all source file headers
  - Updated all documentation

### 🔧 Technical Improvements
- New level classes in separate header files:
  - `AdvancedLevels.hpp` (Levels 4-7)
  - `AdvancedLevels2.hpp` (Levels 8-10)
  - `BossLevel.hpp` (Level 11 + boss system)
- Boss core system with individual vulnerabilities
- Boss projectile system for 5D combat
- Dynamic platform system for changing geometry
- Enhanced game state management for boss phases

### 📊 Statistics
- **Code**: Increased from ~2,300 to ~7,000+ lines
- **Levels**: 3 → 11 levels (267% increase!)
- **Documentation**: ~2,000 → ~26,000 words
- **Files**: 25 → 30+ files

---

## Version 1.0.0 - Initial Release (2025-10-28)

### 🎮 Core Features
- Full 5D spatial representation (X, Y, Z, W, V)
- 10 different dimensional views
- Smooth dimension rotation with interpolation
- Real-time 5D physics simulation
- AABB collision detection in 5D space

### 🏃 Player Mechanics
- Jump (including wall-jump)
- Dash with cooldown
- Wall-slide mechanics
- Movement in current 3D slice

### 🌀 Dimensional System
- All 10 dimensional views accessible
- Smooth transitions between views
- Visual feedback:
  - Opacity based on hidden dimension distance
  - Scale based on hidden dimension distance
  - Color tint indicating W and V positions

### 🎯 Initial Levels
- Level 1: Introduction to 5D
- Level 2: Moving Platforms
- Level 3: Hypercube Maze

### 🎨 Rendering
- OpenGL 4.5+ graphics pipeline
- Custom GLSL shaders (vertex + fragment)
- Phong lighting model
- Alpha blending for transparency
- ImGui debug interface

### 📝 Documentation
- README.md (complete user manual)
- ARCHITECTURE.md (technical details)
- QUICKSTART.md (controls reference)
- INSTALL.md (installation guide)
- PROJECT_SUMMARY.md (overview)
- START_HERE.md (quick start)

### 🛠️ Build System
- CMake configuration
- Automated build script (build.sh)
- Tar.gz packaging
- .gitignore for version control

### 💾 Game Systems
- Save/load system for progress
- Level completion detection
- Automatic level advancement
- Level restart functionality

### 📦 Project Statistics
- 25 files total
- ~2,300 lines of C++20 code
- ~2,000 lines of documentation
- 11 source files
- 2 shader files
- 7 documentation files

---

## Roadmap / Future Versions

### Planned Features
- **Audio System**: Music and sound effects
- **More Bosses**: Additional 5D enemies
- **Level Editor**: Create custom 5D levels
- **Multiplayer**: Synchronized dimensional views
- **Speedrun Mode**: Time attack challenges
- **Achievement System**: Track player accomplishments
- **VR Support**: Enhanced spatial perception
- **Procedural Generation**: Infinite 5D mazes

### Community Contributions
This project is public domain - contributions are welcome!
- Submit pull requests on GitHub
- Share level designs and ideas
- Report bugs and suggest improvements
- Create mods and extensions

---

## Credits

**Original Concept**: Inspired by Miegakure by Marc Ten Bosch  
**Development**: Educational demonstration project  
**License**: The Unlicense (Public Domain)  
**Technologies**: C++20, OpenGL 4.5, SDL2, GLM, GLEW, ImGui

---

**Thank you for playing HyperSpace5D!** 🚀✨

*For technical details, see [ARCHITECTURE.md](ARCHITECTURE.md)*  
*For gameplay help, see [LEVEL_DESIGN.md](LEVEL_DESIGN.md)*  
*For quick start, see [START_HERE.md](START_HERE.md)*
