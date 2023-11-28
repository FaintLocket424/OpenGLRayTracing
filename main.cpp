#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"
#include "camera.h"

#include <iostream>

#include <stacktrace>

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xPos, double yPos);

void processInput(GLFWwindow *window);

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

int WINDOWED_SCR_WIDTH = 1280;
int WINDOWED_SCR_HEIGHT = 720;

float deltaTime = 0.0f;

float lastX;
float lastY;

bool firstMouse = true;

GLFWmonitor *monitor;

bool fullScreen = true;

Camera camera = Camera(vec2(1280, 720), vec3(0.0f, 0.0f, 3.0f));

void trace() {
    auto trace = stacktrace::current();
    for (const auto &entry: trace) {
        cout << "Description: " << entry.description() << '\n';
        cout << "file: " << entry.source_file() << '\n';
        cout << "line: " << entry.source_line() << '\n';
        cout << "------------------------------------------\n";
    }
}

int main() {
//    trace();


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    lastX = (float)mode->width / 2.0f;
    lastY = (float)mode->height / 2.0f;

    GLFWwindow *window;

    if (fullScreen) {
        window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", monitor, nullptr);
    }
    else
    {
        window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", nullptr, nullptr);
    }

    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // FRONT
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // A TOP LEFT
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // B TOP RIGHT
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // C BOTTOM RIGHT
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // D BOTTOM LEFT

            // BOTTOM
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // D TOP LEFT
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // C TOP RIGHT
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // G BOTTOM RIGHT
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // H BOTTOM LEFT

            // BACK
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // F TOP LEFT
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // E TOP RIGHT
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // H BOTTOM RIGHT
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // G BOTTOM LEFT

            // TOP
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // E TOP LEFT
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // F TOP RIGHT
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // B BOTTOM RIGHT
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // A BOTTOM LEFT

            // LEFT
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // E TOP LEFT
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // A TOP RIGHT
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // D BOTTOM RIGHT
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // H BOTTOM LEFT

            // RIGHT
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // B TOP LEFT
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // F TOP RIGHT
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // G BOTTOM RIGHT
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // C BOTTOM LEFT
    };

    int indices[] = {
            0, 2, 1,
            0, 3, 2,

            0 + 4, 2 + 4, 1 + 4,
            0 + 4, 3 + 4, 2 + 4,

            0 + 8, 2 + 8, 1 + 8,
            0 + 8, 3 + 8, 2 + 8,

            0 + 12, 2 + 12, 1 + 12,
            0 + 12, 3 + 12, 2 + 12,

            0 + 16, 2 + 16, 1 + 16,
            0 + 16, 3 + 16, 2 + 16,

            0 + 20, 2 + 20, 1 + 20,
            0 + 20, 3 + 20, 2 + 20,
    };
    // world space positions of our cubes
    vec3 cubePositions[] = {
            vec3(0.0f, 0.0f, 0.0f),
            vec3(2.0f, 5.0f, -15.0f),
            vec3(-1.5f, -2.2f, -2.5f),
            vec3(-3.8f, -2.0f, -12.3f),
            vec3(2.4f, -0.4f, -3.5f),
            vec3(-1.7f, 3.0f, -7.5f),
            vec3(1.3f, -2.0f, -2.5f),
            vec3(1.5f, 2.0f, -2.5f),
            vec3(1.5f, 0.2f, -1.5f),
            vec3(-1.3f, 1.0f, -1.5f)
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("assets/textures/to-to-table.png", &width, &height,
                                    &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("assets/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


//    vec3 cameraTarget(0.0f, 0.0f, 0.0f);

    float lastFrame = 0.0f;


    while (!glfwWindowShouldClose(window)) {
//        cout << "fps: " << 1.0f / deltaTime << '\n';
        auto currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        // create transformations
        mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

//        mat4 projection = mat4(1.0f);
//        projection = perspective(radians(camera.Fov), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        mat4 projection = camera.GetProjectionMatrix();
        ourShader.setMat4("projection", projection);


        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            mat4 model = mat4(1.0f);
            model = translate(model, cubePositions[i]);
            auto angle = (float)(20 * i);
            model = rotate(model, radians(angle), normalize(vec3(0, 1.0f, 0)));
            ourShader.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_F11: {
            if (action != GLFW_PRESS) break;
            if (fullScreen) {
                fullScreen = false;

                camera.UpdateResolution(ivec2(WINDOWED_SCR_WIDTH, WINDOWED_SCR_HEIGHT));

                glfwSetWindowMonitor(window, nullptr, 200, 200, camera.GetResolution().x, camera.GetResolution().y, 0);
            } else {
                fullScreen = true;
                const GLFWvidmode *mode = glfwGetVideoMode(monitor);
                WINDOWED_SCR_WIDTH = camera.GetResolution().x;
                WINDOWED_SCR_HEIGHT = camera.GetResolution().y;
                camera.UpdateResolution(ivec2(mode->width, mode->height));
                glfwSetWindowMonitor(window, monitor, 0, 0, camera.GetResolution().x, camera.GetResolution().y, mode->refreshRate);
            }
            break;
        }

        case GLFW_KEY_F10: {
            if (action != GLFW_PRESS) break;
            cout << "TOGGLE RAY TRACING\n";
        }

        default: {
            break;
        }
    }
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    cout << "mouse_callback\n";
    if (firstMouse) {
        lastX = (float)xPos;
        lastY = (float)yPos;
        firstMouse = false;
    }
    float xOffset = (float)xPos - lastX;
    float yOffset = lastY - (float)yPos;
    lastX = (float)xPos;
    lastY = (float)yPos;
    cout << "lastX: " << lastX << " lastY: " << lastY << '\n';

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    if (width != 0 && height != 0) {
        camera.UpdateResolution(ivec2(width, height));
    }
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}