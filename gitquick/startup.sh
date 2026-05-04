#!/usr/bin/env bash

set -euo pipefail

# 📁 Variables
BUILD_DIR="build"
PKG_DIR="pkg"

echo "🔧 Starting build process..."

# 📁 Création des dossiers
mkdir -p "$BUILD_DIR"
mkdir -p "$PKG_DIR"

cd "$BUILD_DIR"

echo "⚙️ Configuring project with CMake..."
cmake ..

echo "🏗️ Building project..."
make -j$(nproc)

echo "📦 Generating .deb package..."
cpack

echo "📂 Moving package to $PKG_DIR..."
mv *.deb "../$PKG_DIR/"

echo "✅ Build and packaging completed successfully!"