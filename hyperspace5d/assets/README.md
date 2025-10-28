# Assets Directory

This directory contains game assets such as textures, level data, and other resources.

## Directory Structure

- `textures/` - Texture files for game objects
- `levels/` - Level definition files (JSON or custom format)

## Adding New Assets

When adding new assets:
1. Place files in the appropriate subdirectory
2. Use descriptive filenames
3. Document any special requirements in this README

## Current Assets

Currently using procedurally generated geometry and colors. Texture support can be added by:
1. Loading texture files in the Renderer class
2. Adding texture coordinates to the Mesh class
3. Updating shaders to sample textures
