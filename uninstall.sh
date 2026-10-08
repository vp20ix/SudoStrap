#!/bin/bash
# SudoStrap Uninstall Script

echo "🗑  Removing SudoStrap..."

INSTALL_DIR="$HOME/.local"
sudo rm -f "$INSTALL_DIR/bin/sudostrap"
sudo rm -f "$INSTALL_DIR/share/applications/sudostrap.desktop"
sudo rm -f "$INSTALL_DIR/share/icons/hicolor/512x512/apps/sudostrap.png"

echo "✅ SudoStrap removed."
