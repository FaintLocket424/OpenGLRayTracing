#include <iostream>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <filesystem>
#include <limits>
#include <fstream>
#include <iterator>

using namespace std;
using namespace glm;

const char *vertexShaderSource = "#version 460 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        cout << "GLFW Failed to initiate\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const unsigned int windowWidth = 1280;
    const unsigned int windowHeight = 720;

    // Create a GLFW window.
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Ray Tracing", NULL, NULL);

    if (window == NULL) {
        cout << "Failed to create GLFW Window\n";
        glfwTerminate();
        return 2;
    }

    // Set the window to the current context.
    glfwMakeContextCurrent(window);

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialise GLAD\n";
        return 3;
    }

    // Set the viewport size to the window size.
    glViewport(0, 0, windowWidth, windowHeight);

    // Set up the callback function when the window size is changed.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the background colour for the window.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Simple NDC data to render a triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    // Create a vertex buffer object to store our vertices on the GPU.
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Set the VBO as the active Array Buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertices data into the buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create a shader and store an ID number for it.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach the shader source code and compile.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }

    while (!glfwWindowShouldClose(window)) {
        // Input Processing
        processInput(window);

        // Rendering Processing
        glClear(GL_COLOR_BUFFER_BIT);

        // Polling and buffer swapping
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}
