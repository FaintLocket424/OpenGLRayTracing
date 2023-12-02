cmake_minimum_required(VERSION 3.26)
project(openGLRayTracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(openGLRayTracer
        main.cpp
        shader_s.h
        libraries/stb_image.h
        camera.h
        texture.h
        texture.cpp
)

add_subdirectory(glad/)
target_link_libraries(openGLRayTracer glad)

target_link_libraries(openGLRayTracer "C:/cppLibs/glfw/lib-vc2022/glfw3.lib")
target_link_libraries(openGLRayTracer "C:/cppLibs/glfw/lib-vc2022/glfw3_mt.lib")
target_link_libraries(openGLRayTracer "C:/cppLibs/glfw/lib-vc2022/glfw3dll.lib")

include_directories(libraries)
include_directories("C:/cppLibs/glm/glm")
include_directories("C:/cppLibs/glad/include")
include_directories("C:/cppLibs/glfw/include")