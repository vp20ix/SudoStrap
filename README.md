<div align="center">

<img src="resources/icons/logo.jpg" alt="SudoStrap Logo" width="200" />

# ⚡ SudoStrap

**A modern FastFlags manager for Roblox on Linux**

[![Made with C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Qt6](https://img.shields.io/badge/Qt-6.11-green.svg)](https://qt.io)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform: Linux](https://img.shields.io/badge/Platform-Linux-orange.svg)]()
[![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)]()

*A beautiful, fast, and native Linux alternative to Bloxstrap*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Building](#-building-from-source) • [FAQ](#-faq)

</div>

---

## 📖 About

**SudoStrap** is a modern GUI tool for managing Roblox FastFlags on Linux. It provides a clean, native interface to control Sober (Roblox for Linux) settings without editing JSON files manually.

Built with **C++17** and **Qt6**, SudoStrap offers a smooth, native Linux experience with a focus on performance, usability, and beautiful design.

---

## ✨ Features

### ⚡ Performance Tuning
- **Unlock FPS** — Bypass Roblox's default 60 FPS cap
- **Reduce Render Distance** — Lower far-object detail for more FPS
- **Disable Shadows** — Remove dynamic shadows for a large FPS boost
- **Disable Post-Processing** — Remove bloom, depth of field, and sun rays
- **Custom FPS Limit** — Set any framerate you want

### 🎨 Graphics Control
- **Grass Textures** — Toggle grass rendering
- **Texture Quality** — Lowest / Low / Medium / High
- **Lighting Mode** — Voxel / ShadowMap / Future
- **Anti-Aliasing** — Control edge smoothing
- **Gray Sky** — Replace sky with gray for performance

### 🌐 Network Boost
- **60 Hz tick rate** — Smoother network communication
- **Physics interpolation** — Reduced visual lag
- **Low latency mode** — Optimized packet handling
- **Bandwidth tuning** — Better connection stability

### 🎯 Quick Presets
- **🚀 Performance** — Maximum FPS, minimum quality
- **⚖️ Balanced** — Great FPS with decent visuals
- **🎨 Quality** — Best visuals for high-end PCs

### 🔧 FastFlags Editor
- **Add custom flags** — Manual entry with validation
- **Import from file** — Load flags from JSON
- **Export to file** — Save your configuration
- **Paste JSON directly** — Quick setup
- **Search & filter** — Find flags easily

### 🌍 Bilingual UI
- 🇬🇧 **English**
- 🇸🇦 **العربية**
- Instant switching, no restart required

### More Features
- 💾 **Safe saving** — Atomic file writes
- ⚠️ **Process detection** — Warns if Sober is running
- ↺ **Reset to defaults** — One-click reset
- ⚙️ **Auto-update checker** — Silent background checks
- 🎨 **Modern UI** — Glassmorphism-inspired dark theme
- ⚡ **Native performance** — No Electron, no bloat

---

## 📦 Installation

### Requirements

- **Linux** (Fedora, Ubuntu, Arch, etc.)
- **Sober** installed — Download from sober.vinegarhq.org
- **Qt6** runtime libraries

### Quick Install (Fedora)

    sudo dnf install qt6-qtbase qt6-qtsvg

### Ubuntu / Debian

    sudo apt install libqt6widgets6 libqt6svg6

### Arch Linux

    sudo pacman -S qt6-base qt6-svg

---

## 🛠️ Building from Source

### 1. Install Dependencies

**Fedora:**

    sudo dnf install cmake ninja-build gcc-c++ qt6-qtbase-devel qt6-qtsvg-devel

**Ubuntu / Debian:**

    sudo apt install cmake ninja-build g++ qt6-base-dev qt6-svg-dev

**Arch Linux:**

    sudo pacman -S cmake ninja gcc qt6-base qt6-svg

### 2. Clone and Build

    git clone https://github.com/vp20ix/SudoStrap.git
    cd SudoStrap
    cmake -S . -B build -G Ninja
    cmake --build build

### 3. Run

    ./build/SudoStrap

---

## 🚀 Usage

### First Time Setup

1. Launch SudoStrap
2. Configure settings in Performance / Graphics / FastFlags pages
3. Click Save to write to Sober's config file
4. Launch Sober using the sidebar button

### Settings Location

SudoStrap writes to Sober's configuration file:

    ~/.var/app/org.vinegarhq.Sober/config/sober/config.json

SudoStrap does not modify Sober itself — it only manages the config file.

### Quick Presets

In the FastFlags page, enable Preset Mode to access three one-click setups:

| Preset | Best For | Key Settings |
|--------|----------|--------------|
| 🚀 Performance | Low-end PCs | No shadows, no post-FX, FPS unlimited |
| ⚖️ Balanced | Most users | Medium quality, 240 FPS |
| 🎨 Quality | High-end PCs | Max visuals, HD textures, shadows |

### Custom FastFlags

Click "⚙️ Custom FastFlags" to open the editor:

- Add Flag — Manually add a new flag
- Import File — Load flags from a .json file
- Paste JSON — Paste JSON directly
- Export All — Save your flags to a file
- Remove Selected — Delete selected flags

### Backup & Reset

- Save — Writes current settings to config.json
- Reset — Reverts everything to defaults

---

## 📸 Screenshots

Screenshots coming soon — run the app to see the current design!

### Pages
- ⚡ Performance — FPS tuning with toggles
- 🎨 Graphics — Visual quality controls
- 🔧 FastFlags — Advanced flag editor + presets
- ⚙️ Settings — App configuration
- ℹ️ About — Version info + links

---

## 🎨 Tech Stack

| Component | Technology |
|-----------|-----------|
| Language | C++17 |
| Framework | Qt6 (Widgets, Gui, Svg) |
| Build System | CMake + Ninja |
| Styling | Custom QSS |
| Icons | Custom SVG |
| Platform | Linux (X11 + Wayland) |

---

## 📁 Project Structure

    SudoStrap/
    ├── CMakeLists.txt
    ├── LICENSE
    ├── README.md
    ├── .gitignore
    ├── resources/
    │   ├── icons/
    │   │   ├── logo.jpg
    │   │   ├── toggle_on.svg
    │   │   ├── toggle_off.svg
    │   │   ├── arrow_up.svg
    │   │   ├── arrow_down.svg
    │   │   └── chevron_down.svg
    │   └── style.qss
    └── src/
        ├── main.cpp
        ├── core/
        │   ├── configmanager.h
        │   └── configmanager.cpp
        └── ui/
            ├── mainwindow.h
            ├── mainwindow.cpp
            ├── mainwindow.ui
            ├── toggleswitch.h
            ├── toggleswitch.cpp
            ├── customffdialog.h
            ├── customffdialog.cpp
            ├── launchdialog.h
            ├── launchdialog.cpp
            ├── updatedialog.h
            └── updatedialog.cpp

---

## 🤝 Contributing

Contributions are welcome! Here's how:

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

### Development Guidelines

- Follow Qt coding style
- Use Qt6 features only
- Test on Fedora and Ubuntu
- Keep the UI consistent with existing design

---

## 🐛 Bug Reports

Found a bug? Open an issue at https://github.com/vp20ix/SudoStrap/issues with:

- Distribution and version (e.g., Fedora 44)
- Qt version (qmake --version)
- Steps to reproduce
- Expected vs actual behavior
- Screenshots if applicable

---

## 📋 Roadmap

- [x] Core UI (Sidebar + Pages)
- [x] Performance page
- [x] Graphics page
- [x] FastFlags editor
- [x] Custom FastFlags dialog
- [x] Settings page (with language switch)
- [x] About page
- [x] Quick Presets
- [x] Network Boost
- [x] Export/Import flags
- [x] Arabic translation
- [ ] Keyboard shortcuts
- [ ] System tray icon
- [ ] Auto-update (real implementation)
- [ ] Flatpak packaging
- [ ] AppImage release
- [ ] Plugin system

---

## ❓ FAQ

**Is this legal?**
Yes. SudoStrap only edits configuration files that Sober itself exposes. It uses only FastFlags on Roblox's official allowlist.

**Will this get me banned?**
No. SudoStrap doesn't modify Roblox's memory or files — only the config JSON. All flags used are documented and safe.

**Does it work on Wayland?**
Yes. SudoStrap is a native Qt6 app that works on both X11 and Wayland.

**Can I use Bloxstrap FastFlags?**
Partially. Only flags on Roblox's allowlist work. SudoStrap filters them automatically.

**How do I uninstall?**
Just delete the folder:

    rm -rf ~/SudoStrap

SudoStrap doesn't install anything system-wide.

**Where are my settings saved?**
Settings are written to Sober's config file:

    ~/.var/app/org.vinegarhq.Sober/config/sober/config.json

---

## 📄 License

This project is licensed under the **MIT License** — see the LICENSE file for details.

---

## 🙏 Credits

- **Sober** — Roblox runtime for Linux (sober.vinegarhq.org)
- **VinegarHQ** — Sober developers (vinegarhq.org)
- **Bloxstrap** — Original inspiration (github.com/bloxstraplabs/bloxstrap)
- **Qt Project** — Amazing cross-platform framework (qt.io)

---

<div align="center">

<img src="resources/icons/logo.jpg" alt="SudoStrap" width="80" />

**Made with ❤️ for the Linux gaming community**

⭐ If you find SudoStrap useful, please give it a star!

[⬆ Back to top](#-sudostrap)

</div>
