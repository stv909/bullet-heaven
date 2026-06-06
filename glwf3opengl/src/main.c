#include <stdio.h>
#include <webgpu.h>
#include <GLFW/glfw3.h>

void keyboard_callback(GLFWwindow *window, int key, int scancode,
  int action, int mods);

int rotate_y = 0;
int rotate_x = 0;

int main(int argc, char const *argv[])
{
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(320, 320, "Rotate Cube", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // test basic wgpu under glfw
  int platform = glfwGetPlatform();
  printf("GLFW platform: %x\n", platform);
  WGPUInstance instance = wgpuCreateInstance(NULL);
  printf("WGPU instance: %p\n", instance);
  wgpuInstanceRelease(instance);

  glfwMakeContextCurrent(window);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window))
  {
    glfwSetKeyCallback(window, keyboard_callback);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    glBegin(GL_POLYGON); // Yellow side - FRONT
      glColor3f(1.0,  1.0,  0.0);
      glVertex3f( 0.5, -0.5, -0.5);
      glVertex3f( 0.5,  0.5, -0.5);
      glVertex3f(-0.5,  0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_POLYGON); // White side - BACK
      glColor3f(1.0,  1.0, 1.0);
      glVertex3f( 0.5, -0.5, 0.5);
      glVertex3f( 0.5,  0.5, 0.5);
      glVertex3f(-0.5,  0.5, 0.5);
      glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON); // Purple side - RIGHT
      glColor3f(1.0,  0.0,  1.0);
      glVertex3f(0.5, -0.5, -0.5);
      glVertex3f(0.5,  0.5, -0.5);
      glVertex3f(0.5,  0.5,  0.5);
      glVertex3f(0.5, -0.5,  0.5);
    glEnd();

    glBegin(GL_POLYGON); // Green side - LEFT
      glColor3f(0.0,  1.0,  0.0);
      glVertex3f(-0.5, -0.5,  0.5);
      glVertex3f(-0.5,  0.5,  0.5);
      glVertex3f(-0.5,  0.5, -0.5);
      glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_POLYGON); // Blue side - TOP
      glColor3f(0.0,  0.0,  1.0);
      glVertex3f( 0.5,  0.5,  0.5);
      glVertex3f( 0.5,  0.5, -0.5);
      glVertex3f(-0.5,  0.5, -0.5);
      glVertex3f(-0.5,  0.5,  0.5);
    glEnd();

    glBegin(GL_POLYGON); // Red side - BOTTOM
      glColor3f(1.0,  0.0,  0.0);
      glVertex3f( 0.5, -0.5, -0.5);
      glVertex3f( 0.5, -0.5,  0.5);
      glVertex3f(-0.5, -0.5,  0.5);
      glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void keyboard_callback(GLFWwindow* window, int key, int scancode,
  int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    rotate_x += 5;
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    rotate_x -= 5;
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    rotate_y -= 5;
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    rotate_y += 5;
}
