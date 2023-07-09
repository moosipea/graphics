#include "render.h"
#include "glad/gl.h"

int compile_shader(unsigned int shader, const char *src) {
    int success;
    char info_log[512];
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf("Shader compilation error: %s\n", info_log);
        return 0;
    }

    return 1;
}

unsigned int compile_shaders(const char *vertex_src, const char *fragment_src) {
    unsigned int vertex_shader, fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!compile_shader(vertex_shader, vertex_src))
        return 1;
    if (!compile_shader(fragment_shader, fragment_src))
        return 1;

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int success;
    char info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("Program linking error: %s\n", info_log);
        return 0;
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

unsigned int create_vbo(float *vertices, unsigned int n_bytes) {
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, n_bytes, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)0);
    
    return vbo;
}

Mesh create_mesh(float *vertices, unsigned int n_bytes) {
    Mesh m;
    unsigned int vao;
    glGenVertexArrays(1, &vao);

    m.vbo = create_vbo(vertices, n_bytes);
    m.vao = vao;
    m.count = n_bytes / VERTEX_SIZE;

    return m;
}

void Mesh_draw(Mesh mesh) {
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glDrawArrays(GL_TRIANGLES, 0, mesh.count);
}

GLFWwindow* create_window(int width, int height, const char *title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    return glfwCreateWindow(width, height, title, NULL, NULL);
}