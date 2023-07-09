#include <GLFW/glfw3.h>
#include "spritedata.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "graphics"

int main() {
    if (!glfwInit())
        return 1;
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window)
        return 1;

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}