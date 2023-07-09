cmake_minimum_required(VERSION 3.20)
project(graphics C)
add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(external/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE build/external/glfw/src)
target_link_libraries(${PROJECT_NAME} glfw3 gl)
