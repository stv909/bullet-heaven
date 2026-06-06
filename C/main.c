#include "glfw3webgpu/glfw3webgpu.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <webgpu.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	// Init WebGPU
	WGPUInstance instance = wgpuCreateInstance(NULL);

	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Learn WebGPU", NULL, NULL);

	// Here we create our WebGPU surface from the window!
	WGPUSurface surface = glfwCreateWindowWGPUSurface(instance, window);
	printf("surface = %p", (void*)surface);

	// Terminate GLFW
	while (!glfwWindowShouldClose(window)) glfwPollEvents();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
