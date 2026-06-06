cmake_minimum_required(VERSION 3.16)
project(bullet-heaven C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------
# GLFW 3.4+ — built-in WebGPU surface support (glfwGetWGPUSurface)
# ------------------------------------------------------------------
find_package(glfw3 3.4 QUIET)

if(glfw3_FOUND)
    message(STATUS "Using system GLFW ${glfw3_VERSION}")
else()
    message(STATUS "GLFW 3.4 not found — fetching from GitHub (one-time download)")
    include(FetchContent)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
endif()

# ------------------------------------------------------------------
# wgpu-native — Homebrew-installed (v29+)
# ------------------------------------------------------------------
set(WGPU_ROOT "" CACHE PATH "Path to wgpu-native install prefix")

set(_hint_paths "${WGPU_ROOT}")
if(APPLE)
    list(APPEND _hint_paths /usr/local /opt/homebrew)
endif()

find_path(WGPU_INCLUDE_DIR NAMES webgpu.h
    HINTS ${_hint_paths} PATH_SUFFIXES include)
find_library(WGPU_LIBRARY NAMES wgpu_native
    HINTS ${_hint_paths} PATH_SUFFIXES lib)

if(NOT WGPU_INCLUDE_DIR OR NOT WGPU_LIBRARY)
    message(FATAL_ERROR
        "wgpu-native not found.\n"
        "Install:  brew install wgpu-native\n"
        "Or pass:  -DWGPU_ROOT=/path/to/wgpu-native")
endif()

message(STATUS "WGPU include: ${WGPU_INCLUDE_DIR}")
message(STATUS "WGPU library: ${WGPU_LIBRARY}")

add_library(wgpu_native SHARED IMPORTED)
set_target_properties(wgpu_native PROPERTIES
    IMPORTED_LOCATION "${WGPU_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${WGPU_INCLUDE_DIR}")

# ------------------------------------------------------------------
# Target
# ------------------------------------------------------------------
add_executable(bullet-heaven src/main.c)

target_link_libraries(bullet-heaven PRIVATE glfw wgpu_native)

# OpenGL — framework on macOS, find_package on Linux/Windows
if(APPLE)
    target_link_libraries(bullet-heaven PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(bullet-heaven PRIVATE OpenGL::GL)
endif()

# Copy the .dylib next to the binary so it's found at runtime (macOS)
if(APPLE)
    add_custom_command(TARGET bullet-heaven POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${WGPU_LIBRARY}"
            "$<TARGET_FILE_DIR:bullet-heaven>/")
endif()
