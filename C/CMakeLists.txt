# This example comes from https://eliemichel.github.io/LearnWebGPU
cmake_minimum_required(VERSION 3.11.0...3.25.0)
project(glfw3webgpu-examples VERSION 1.0.0 LANGUAGES C)

include(FetchContent)
include(utils.cmake)

# Dependencies
if (EMSCRIPTEN)

  add_library(glfw INTERFACE)
  target_link_options(glfw INTERFACE -sUSE_GLFW=3)

  add_library(webgpu INTERFACE)
  target_link_options(webgpu INTERFACE -sUSE_WEBGPU=1)
  function(target_copy_webgpu_binaries)
  endfunction()

else (EMSCRIPTEN)

  FetchContent_Declare(
    glfw-light
    URL      https://eliemichel.github.io/LearnWebGPU/_downloads/6873a344e35ea9f5e4fc7e5cc85d3ab8/glfw-3.4.0-light.zip
    URL_HASH MD5=e6684142080457e9227e4f78a6f84fc2
  )
  FetchContent_Declare(
    webgpu
    URL https://github.com/eliemichel/WebGPU-distribution/archive/refs/tags/wgpu-v24.0.0.2.zip
    URL_HASH MD5=8497f91384b866ba5bf2458b7281f647
  )
  FetchContent_MakeAvailable(glfw-light webgpu)

endif (EMSCRIPTEN)

# The glfw3webgpu target
add_subdirectory(glfw3webgpu)

# Example
add_executable(bullet-heaven main.c)
target_link_libraries(bullet-heaven PRIVATE glfw webgpu glfw3webgpu)
set_target_properties(bullet-heaven PROPERTIES CXX_STANDARD 17)
target_treat_all_warnings_as_errors(bullet-heaven)
target_copy_webgpu_binaries(bullet-heaven)
