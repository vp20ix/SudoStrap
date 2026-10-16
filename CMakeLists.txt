cmake_minimum_required(VERSION 3.16)

project(SudoStrap
    VERSION 0.1.0
    DESCRIPTION "FastFlags Manager for Sober on Linux"
    LANGUAGES CXX
)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt6 auto-tools (moc, uic, rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Svg)

# Sources
set(SOURCES
    src/main.cpp
    src/ui/mainwindow.cpp
    src/ui/customffdialog.cpp
    src/ui/launchdialog.cpp
    src/ui/toggleswitch.cpp
    src/ui/updatedialog.cpp
    src/core/configmanager.cpp
)

set(HEADERS
    src/ui/mainwindow.h
    src/ui/customffdialog.h
    src/ui/launchdialog.h
    src/ui/toggleswitch.h
    src/ui/updatedialog.h
    src/core/configmanager.h
)

set(FORMS
    src/ui/mainwindow.ui
)

# Executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

# Link Qt6
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)