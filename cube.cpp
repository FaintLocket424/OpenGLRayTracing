#include "cube.h"

float Cube::Vertices[] = {
        // FRONT
        -0.5f, +0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // A TOP LEFT
        +0.5f, +0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // B TOP RIGHT
        +0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // C BOTTOM RIGHT
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // D BOTTOM LEFT

        // BOTTOM
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // D TOP LEFT
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // C TOP RIGHT
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // G BOTTOM RIGHT
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // H BOTTOM LEFT

        // BACK
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,// F TOP LEFT
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// E TOP RIGHT
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // H BOTTOM RIGHT
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // G BOTTOM LEFT

        // TOP
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // E TOP LEFT
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // F TOP RIGHT
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // B BOTTOM RIGHT
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // A BOTTOM LEFT

        // LEFT
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // E TOP LEFT
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // A TOP RIGHT
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // D BOTTOM RIGHT
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // H BOTTOM LEFT
        \
            // RIGHT
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // B TOP LEFT
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // F TOP RIGHT
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // G BOTTOM RIGHT
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // C BOTTOM LEFT
};

unsigned int Cube::Indices[] = {
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



Cube::Cube(glm::vec3 pos) {
    position = pos;
}

vec3 Cube::GetPosition() {
    return position;
}

//float* Cube::GetVertices() {
//    return vertices;
//}
//
//unsigned int* Cube::GetIndices() {
//    return indices;
//}