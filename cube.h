#ifndef CUBE_H
#define CUBE_H


#include <glm/vec3.hpp>

using glm::vec3;

class Cube {
private:
    vec3 position{};



public:
    static float Vertices[191];

    static unsigned int Indices[35];

    Cube(vec3 pos);
    vec3 GetPosition();
//    static float* GetVertices();
//    static unsigned int* GetIndices();
};

#endif //CUBE_H
