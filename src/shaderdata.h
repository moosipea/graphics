#ifndef SHADERDATA_H
#define SHADERDATA_H
const char *VERTEX_SHADER_SOURCE = "// #version 330 core\n// \n// layout (location = 0) in vec3 aPos;\n// layout (location = 1) in vec3 aColor;\n// layout (location = 2) in vec3 aTexCoord;\n// \n// out vec3 ourColor;\n// out vec2 TexCoord;\n// \n// void main() {\n//     gl_Position = vec4(aPos, 1.0);\n//     ourColor = aColor;\n//     TexCoord = aTexCoord;\n// };\n#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main()\n{\n    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
const char *FRAGMENT_SHADER_SOURCE = "// #version 330 core\n// \n// out vec4 FragColor;\n// in vec3 ourColor;\n// in vec2 TexCoord;\n// \n// uniform sampler2D ourTexture;\n// \n// void main() {\n//     FragColor = vec4(ourColor, 1.0) * texture(ourTexture, TexCoord);\n// }\n#version 330 core\nout vec4 FragColor;\n\nvoid main()\n{\n    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n} ";
#endif
