#include <stdio.h>

#include "render.h"
#include "spritedata.h"
#include "shaderdata.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "graphics"

void texture_business() {
    unsigned int texture;
    glGenTextures(1, &texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_INT, &ATLAS);
    glGenerateMipmap(GL_TEXTURE_2D);
}

int main() {
    if (!glfwInit())
        return 1;
    
    GLFWwindow *window = create_window(WIDTH, HEIGHT, TITLE);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    
    //texture_business();
    

    unsigned int shader_program = compile_shaders(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
    if (!shader_program) {
        glfwTerminate();
        return 1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    Mesh mesh = create_mesh(vertices, sizeof(vertices));
    printf("Mesh\n\tvbo = %d\n\tvao = %d", mesh.vbo, mesh.vao);

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        Mesh_draw(mesh); // I don't know why it's not showing up

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}