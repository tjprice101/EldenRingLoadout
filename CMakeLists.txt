cmake_minimum_required(VERSION 3.10)
project(EldenRingLoadout)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Include directories ---
include_directories(
    "${PROJECT_SOURCE_DIR}/Header Files"      # contains Spell.h, Spells.h, etc.
    "${PROJECT_SOURCE_DIR}/Loadout"
    "${PROJECT_SOURCE_DIR}/IO"
    "${PROJECT_SOURCE_DIR}/imgui"             # imgui.h lives here
    "${PROJECT_SOURCE_DIR}/imgui/backends"    # backend headers
)

# --- Find GLFW ---
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# --- Load source files ---
file(GLOB LOADOUT_SOURCES "Loadout/*.cpp")  # includes Spell.cpp and Spells.cpp
file(GLOB IO_SOURCES "IO/*.cpp")

# ImGui sources
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# --- Add executable ---
add_executable(eldenring
    main.cpp
    ${LOADOUT_SOURCES}
    ${IO_SOURCES}
    ${IMGUI_SOURCES}
)

# --- Link libraries ---
target_link_libraries(eldenring
    ${GLFW_LIBRARIES}
    GL
    pthread
    dl
)
