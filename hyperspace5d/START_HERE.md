# 🚀 HyperSpace5D - START HERE

## Welcome to the Fifth Dimension!

You've just unpacked **HyperSpace5D**, a 5-dimensional puzzle platformer game. This guide will get you started in under 5 minutes.

---

## 🎮 What is This?

A puzzle platformer where you navigate through **five spatial dimensions** (X, Y, Z, W, V). You can only see 3 dimensions at a time, creating mind-bending puzzles where platforms appear and disappear as you rotate your view.

---

## ⚡ Quick Start (Arch Linux)

```bash
# 1. Install dependencies (one command)
yay -S base-devel cmake gcc glm sdl2 glew imgui

# 2. Build the game (one command)
./build.sh

# 3. Run the game
cd build
./HyperSpace5D
```

**That's it!** 🎉

---

## 📖 Documentation Guide

We've prepared comprehensive documentation. Here's where to start:

### For Players
1. **[QUICKSTART.md](QUICKSTART.md)** ← Start here for controls and basic concepts
2. **[README.md](README.md)** ← Full game manual with all features

### For Developers
3. **[ARCHITECTURE.md](ARCHITECTURE.md)** ← Technical implementation details
4. **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** ← Project overview and statistics

### For Installation
5. **[INSTALL.md](INSTALL.md)** ← Detailed installation guide and troubleshooting

### For Review
6. **[COMPLETION_REPORT.md](COMPLETION_REPORT.md)** ← Complete project status report

---

## 🎯 Essential Controls

| Key | Action |
|-----|--------|
| **WASD** | Move |
| **Space** | Jump |
| **Shift** | Dash |
| **Q / E** | Rotate dimensions |
| **R** | Return to normal 3D view |
| **F3** | Toggle debug info |

---

## 🧠 Understanding 5D in 60 Seconds

1. **You exist in 5D space**: Your position has 5 coordinates (X, Y, Z, W, V)
2. **You see 3D slices**: You can only view 3 dimensions at once
3. **Objects exist in all 5D**: When you rotate dimensions, hidden objects appear
4. **Solve puzzles**: Use dimension rotation to find paths and reach the goal

**Visual Cues:**
- 🌫️ **Transparency**: Objects far in hidden dimensions are ghostly
- 📏 **Size**: Objects shrink with distance in hidden dimensions  
- 🎨 **Color**: Tints indicate position in the 4th and 5th dimensions

---

## 🏆 The Eleven Levels

### Early Game (Levels 1-3)
**Introduction to 5D**: Basic mechanics, dimension rotation, simple mazes
**Difficulty**: ⭐☆☆

### Mid Game (Levels 4-7)
**Advanced Puzzles**: Pentacube maze, dimensional bridges, portals, phase objects
**Difficulty**: ⭐⭐☆

### Late Game (Levels 8-10)
**Mastery Required**: Rotation locks, temporal echoes, hypersurface walking
**Difficulty**: ⭐⭐⭐

### Boss (Level 11)
**The Pentarch**: Epic 5D boss fight with 5 cores, dynamic arena, and all mechanics!
**Difficulty**: ⭐⭐⭐⭐⭐

**See [LEVEL_DESIGN.md](LEVEL_DESIGN.md) for detailed walkthrough!**

---

## 🔧 Installation Issues?

### Common Problems

**OpenGL Error?**
```bash
glxinfo | grep "OpenGL version"  # Check version
# Update GPU drivers if needed
```

**ImGui Not Found?**
```bash
yay -S imgui  # Install ImGui
```

**Shaders Missing?**
```bash
cd build
cp -r ../shaders .  # Copy shaders
```

For more help, see **[INSTALL.md](INSTALL.md)**

---

## 📁 Project Structure

```
hyperspace5d/
├── START_HERE.md          ← You are here!
├── QUICKSTART.md          ← Quick reference
├── README.md              ← Full manual
├── ARCHITECTURE.md        ← Technical docs
├── build.sh               ← Build script
├── CMakeLists.txt         ← Build config
├── src/                   ← Source code
│   ├── core/              ← 5D math
│   ├── engine/            ← Game engine
│   ├── game/              ← Game logic
│   └── main.cpp           ← Entry point
├── shaders/               ← GLSL shaders
└── assets/                ← Game resources
```

---

## 💡 Pro Tips

1. **Lost?** Press **R** to return to standard XYZ view
2. **Stuck?** Press **ESC** to restart the level
3. **Can't reach a platform?** Try pressing **Q** or **E** to see other dimensions
4. **Moving too fast?** Use **Shift** dash strategically
5. **Need info?** Press **F3** for debug panel

---

## 🎓 What You'll Learn

By playing HyperSpace5D, you'll gain intuition about:
- Higher-dimensional geometry
- Projective visualization
- Spatial reasoning in 5D
- Linear algebra concepts
- Creative problem-solving

---

## 🛠️ Technology Stack

- **Language**: C++20
- **Graphics**: OpenGL 4.5
- **Math**: GLM (OpenGL Mathematics)
- **Window/Input**: SDL2
- **UI**: ImGui
- **Build**: CMake

---

## 📊 Quick Stats

| Metric | Value |
|--------|-------|
| Dimensions | 5 (X, Y, Z, W, V) |
| Possible Views | 10 |
| Levels | **11** (including boss!) |
| Lines of Code | 7,000+ |
| Documentation | 8 comprehensive guides |

---

## 🆘 Need Help?

1. Check **[QUICKSTART.md](QUICKSTART.md)** for controls
2. See **[INSTALL.md](INSTALL.md)** for installation issues
3. Read **[README.md](README.md)** for detailed information
4. Review **[ARCHITECTURE.md](ARCHITECTURE.md)** for technical details

---

## 🎮 Ready to Play?

```bash
./build.sh
cd build
./HyperSpace5D
```

**Press F4 in-game for help!**

---

## 🌟 Have Fun!

You're about to experience something truly unique: **navigation through five spatial dimensions**. 

Take your time, experiment with the controls, and enjoy the mind-bending puzzles!

**Welcome to HyperSpace!** 🚀✨

---

## 📝 Quick Command Reference

```bash
# Install dependencies
yay -S base-devel cmake gcc glm sdl2 glew imgui

# Build
./build.sh

# Run
cd build && ./HyperSpace5D

# Clean build
rm -rf build && ./build.sh

# Create package
./build.sh  # Creates hyperspace5d-1.0.0.tar.gz
```

---

**For complete documentation, start with [QUICKSTART.md](QUICKSTART.md)**
