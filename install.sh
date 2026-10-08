#!/bin/bash
# SudoStrap Installation Script

set -e

echo "⚡ SudoStrap Installer"
echo "======================"
echo ""

# Check dependencies
echo "→ Checking dependencies..."
if ! command -v cmake &> /dev/null; then
    echo "❌ cmake not found. Install it first."
    exit 1
fi

# Build
echo "→ Building SudoStrap..."
cmake -S . -B build -G Ninja
cmake --build build

# Install
echo "→ Installing to system..."
INSTALL_DIR="$HOME/.local"
sudo install -Dm755 build/SudoStrap "$INSTALL_DIR/bin/sudostrap"
sudo install -Dm644 resources/sudostrap.desktop "$INSTALL_DIR/share/applications/sudostrap.desktop"
sudo install -Dm644 resources/icons/logo_banner.png "$INSTALL_DIR/share/icons/hicolor/512x512/apps/sudostrap.png"

# Update desktop database
if command -v update-desktop-database &> /dev/null; then
    update-desktop-database "$INSTALL_DIR/share/applications" 2>/dev/null || true
fi

echo ""
echo "✅ SudoStrap installed successfully!"
echo ""
echo "Launch from:"
echo "  • Applications menu → SudoStrap"
echo "   • Terminal: sudostrap"
echo ""
