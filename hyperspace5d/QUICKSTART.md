# HyperSpace5D - Quick Start Guide

## Installation (Arch Linux)

```bash
# Install dependencies
yay -S base-devel cmake gcc glm sdl2 glew imgui

# Extract the game
tar -xzf hyperspace5d-1.0.0.tar.gz
cd hyperspace5d-1.0.0

# Build and run
./build.sh
cd build
./HyperSpace5D
```

## Essential Controls

| Key | Action |
|-----|--------|
| **W/A/S/D** | Move in current 3D view |
| **Space** | Jump |
| **Shift** | Dash |
| **Q** | View XYW dimensions |
| **E** | View XYV dimensions |
| **R** | Return to XYZ (standard 3D) |
| **1-9** | Quick dimension switches |
| **ESC** | Restart level |
| **F1/F2** | Previous/Next level |
| **F3** | Toggle debug UI |

## Understanding 5D Space

### The Five Dimensions
- **X, Y, Z**: Standard 3D space (left/right, up/down, forward/back)
- **W**: Fourth dimension (perpendicular to X, Y, Z)
- **V**: Fifth dimension (perpendicular to X, Y, Z, W)

### Visual Cues
- **Transparency**: Objects far in hidden dimensions are more transparent
- **Size**: Objects shrink with distance in hidden dimensions
- **Color**: Warm/cool tints indicate position in W and V

### Basic Strategy
1. Start in XYZ view (standard 3D)
2. Look for platforms that seem unreachable
3. Press **Q** or **E** to rotate dimensions
4. Watch for platforms appearing/disappearing
5. Jump when platforms intersect your current view

## Level Goals

### Level 1: Introduction
Learn to rotate dimensions. Find the hidden platform by switching to XYW view.

### Level 2: Moving Platforms
Time your jumps as platforms move through hidden dimensions.

### Level 3: Hypercube Maze
Navigate walls that exist in some views but not others.

## Troubleshooting

**Can't see any platforms?**
- Try pressing **1** to reset to XYZ view
- Press **Q** or **E** to see other dimensional views

**Fell off the map?**
- Press **ESC** to restart the level

**Performance issues?**
- Press **F3** to check FPS
- Make sure GPU drivers are updated

## Tips

1. **Move in Hidden Dimensions**: Even in XYZ view, you can move in W or V by switching views temporarily
2. **Wall Jumping**: You can jump off walls! Use this to reach higher platforms
3. **Dash in Air**: Use dash to extend jumps or change direction mid-air
4. **Watch the Indicator**: The debug UI shows your current dimensional view

---

**Have fun exploring hyperspace!** 🚀
