cmake_minimum_required(VERSION 3.16)
project(bullet-heaven C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------
# GLFW 3.x
# ------------------------------------------------------------------
find_package(glfw3 3.3 QUIET)

if(glfw3_FOUND)
    message(STATUS "Using system GLFW ${glfw3_VERSION}")
else()
    message(STATUS "GLFW not found — fetching from GitHub (one-time download)")
    include(FetchContent)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.9
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
endif()

# ------------------------------------------------------------------
# Target
# ------------------------------------------------------------------
add_executable(bullet-heaven src/main.c)

target_link_libraries(bullet-heaven PRIVATE glfw)

# OpenGL — framework on macOS, find_package on Linux/Windows
if(APPLE)
    target_link_libraries(bullet-heaven PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(bullet-heaven PRIVATE OpenGL::GL)
endif()
