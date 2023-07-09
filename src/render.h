#ifndef RENDER_H
#define RENDER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define VERTEX_SIZE (3 * sizeof(float))

typedef struct Mesh {
    unsigned int vbo;
    unsigned int vao;
    unsigned int count;
} Mesh;

GLFWwindow* create_window(int width, int height, const char *title);
unsigned int compile_shaders(const char *vertex_src, const char *fragment_src);
Mesh create_mesh(float *vertices, unsigned int n_bytes);
void Mesh_draw(Mesh mesh);
#endif