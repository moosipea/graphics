cmake_minimum_required(VERSION 3.20)
project(graphics C)
add_executable(${PROJECT_NAME} src/main.c src/render.c)

add_subdirectory(external/glfw)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/external/glad")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE build/external/glfw/src)
target_link_libraries(${PROJECT_NAME} PUBLIC glad_gl_core_33 glfw3)
