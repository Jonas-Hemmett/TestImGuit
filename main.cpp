#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;
int main()
{
    glfwInit();
    GLFWwindow* w = glfwCreateWindow(800, 600, "Test", 0, 0);
    glfwMakeContextCurrent(w);

    while (!glfwWindowShouldClose(w)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
    return 0;
}