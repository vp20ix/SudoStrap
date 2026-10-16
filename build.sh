#!/usr/bin/env bash
set -e

echo "🔧 SudoStrap Builder"
echo "===================="
echo ""

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    echo "❌ Cannot detect distribution"
    exit 1
fi

echo "📦 Installing dependencies for $DISTRO..."
echo ""

case $DISTRO in
    fedora|rhel|centos|rocky|almalinux)
        sudo dnf install -y cmake ninja-build gcc-c++ \
            qt6-qtbase-devel qt6-qtsvg-devel
        ;;
    ubuntu|debian|pop|linuxmint|zorin|kali)
        sudo apt update
        sudo apt install -y cmake ninja-build g++ \
            qt6-base-dev qt6-svg-dev
        ;;
    arch|manjaro|endeavouros|garuda)
        sudo pacman -S --noconfirm base-devel cmake ninja \
            qt6-base qt6-svg
        ;;
    opensuse*|suse*|tumbleweed)
        sudo zypper install -y cmake ninja gcc-c++ \
            qt6-base-devel qt6-svg-devel
        ;;
    *)
        echo "❌ Unsupported distribution: $DISTRO"
        echo ""
        echo "Please install manually:"
        echo "  - CMake 3.16+"
        echo "  - Ninja"
        echo "  - C++17 compiler"
        echo "  - Qt6 (base + svg) development packages"
        exit 1
        ;;
esac

echo ""
echo "🔨 Building SudoStrap..."
echo ""

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

echo ""
echo "🎨 Installing style.qss..."
mkdir -p ~/.local/share/sudostrap
cp resources/style.qss ~/.local/share/sudostrap/style.qss

echo ""
echo "✅ Build complete!"
echo ""
echo "Run SudoStrap with:"
echo ""
echo "    ./build/SudoStrap"
echo ""
