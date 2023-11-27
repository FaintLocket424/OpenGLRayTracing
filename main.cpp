#include <iostream>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_s.h"

using namespace std;
using namespace glm;

//const char *vertexShaderSource = "#version 460 core\n"
//                                 "layout (location = 0) in vec3 aPos;\n"
//                                 "layout (location = 1) in vec3 aColor;\n"
//                                 "out vec3 ourColor;\n"
//                                 "void main()\n"
//                                 "{\n"
//                                 "   gl_Position = vec4(aPos, 1.0f);\n"
//                                 "   ourColor = aColor;\n"
//                                 "}\0";
//
//const char *fragmentShaderSource = "#version 460 core\n"
//                                   "out vec4 FragColor;\n"
//                                   "in vec3 ourColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "   FragColor = vec4(ourColor, 1.0f);\n"
//                                   "}\0";

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
            // positions                        // colors
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top
    };

    float texCoords[] = {
            0.0f, 0.0f,  // lower-left corner
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
    };

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    Shader ourShader("assets/vertex.vert", "assets/fragment.frag");

    // Create a vertex buffer object to store our vertices on the GPU.

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        // Input Processing
        processInput(window);

        // Rendering Processing
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Polling and buffer swapping
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}
