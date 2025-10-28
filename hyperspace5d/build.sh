#!/bin/bash

# HyperSpace5D Build and Package Script
# This script builds the game and creates a distributable tarball

set -e  # Exit on error

PROJECT_NAME="hyperspace5d"
VERSION="1.0.0"
BUILD_DIR="build"
PACKAGE_NAME="${PROJECT_NAME}-${VERSION}"

echo "==================================="
echo "HyperSpace5D Build Script"
echo "Version: ${VERSION}"
echo "==================================="

# Clean previous build
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

# Create build directory
echo "Creating build directory..."
mkdir -p "$BUILD_DIR"

# Run CMake
echo "Running CMake..."
cd "$BUILD_DIR"
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "Compiling..."
make -j$(nproc)

echo ""
echo "Build completed successfully!"
echo ""

# Test run (optional - commented out)
# echo "Testing binary..."
# ./HyperSpace5D --version || true

# Return to root directory
cd ..

# Create package
echo "Creating distributable package..."

# Create temporary package directory
PACKAGE_DIR="/tmp/${PACKAGE_NAME}"
rm -rf "$PACKAGE_DIR"
mkdir -p "$PACKAGE_DIR"

# Copy source files
echo "Copying source files..."
cp -r src "$PACKAGE_DIR/"
cp -r shaders "$PACKAGE_DIR/"
cp -r assets "$PACKAGE_DIR/"

# Copy build files
echo "Copying build files..."
cp CMakeLists.txt "$PACKAGE_DIR/"
cp build.sh "$PACKAGE_DIR/"
cp .gitignore "$PACKAGE_DIR/" 2>/dev/null || true

# Copy documentation
echo "Copying documentation..."
cp README.md "$PACKAGE_DIR/"
cp ARCHITECTURE.md "$PACKAGE_DIR/"

# Copy compiled binary
echo "Copying compiled binary..."
cp build/HyperSpace5D "$PACKAGE_DIR/" 2>/dev/null || true

# Create tarball
echo "Creating tarball..."
cd /tmp
tar -czf "${PACKAGE_NAME}.tar.gz" "$PACKAGE_NAME"

# Move to original directory
mv "${PACKAGE_NAME}.tar.gz" -

# Clean up
rm -rf "$PACKAGE_DIR"

# Return to original directory
cd - > /dev/null

echo ""
echo "==================================="
echo "Package created successfully!"
echo "File: ${PACKAGE_NAME}.tar.gz"
echo "Size: $(du -h ${PACKAGE_NAME}.tar.gz | cut -f1)"
echo "==================================="
echo ""
echo "To extract and build:"
echo "  tar -xzf ${PACKAGE_NAME}.tar.gz"
echo "  cd ${PACKAGE_NAME}"
echo "  ./build.sh"
echo ""
echo "Or to install dependencies first:"
echo "  yay -S base-devel cmake gcc glm sdl2 glew imgui"
echo ""

exit 0
