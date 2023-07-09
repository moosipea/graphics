#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "spritedata.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "graphics"

GLFWwindow* create_window(int width, int height, const char *title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
}

int main() {
    if (!glfwInit())
        return 1;
    
    GLFWwindow *window = create_window(WIDTH, HEIGHT, TITLE);
    if (!window)
        return 1;

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}