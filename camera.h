#ifndef OPENGLRAYTRACER_CAMERA_H
#define OPENGLRAYTRACER_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::ivec2, glm::vec3, glm::radians, glm::normalize, glm::cross, glm::mat4, glm::lookAt, glm::clamp, glm::perspective;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float INITIAL_YAW = -90.0f;
const float INITIAL_PITCH = 0.0f;
const float INITIAL_SPEED = 2.5f;
const float INITIAL_SENSITIVITY = 0.1f;
const float INITIAL_FOV = 45.0;
const float INITIAL_NEAR_CLIP = 0.1f;
const float INITIAL_FAR_CLIP = 100.0f;

class Camera {
public:
    Camera(
            ivec2 resolution,
            vec3 position = vec3(0.0f, 0.0f, 0.0f),
            vec3 up = vec3(0.0f, 1.0f, 0.0f),
            float yaw = INITIAL_YAW,
            float pitch = INITIAL_PITCH,
            float nearClip = INITIAL_NEAR_CLIP,
            float farClip = INITIAL_FAR_CLIP
    ):
    WorldUp(up)
    {
        this->resolution = resolution;
        Front = vec3(0.0f, 0.0f, -1.0f);
        MovementSpeed = INITIAL_SPEED;
        MouseSensitivity = INITIAL_SENSITIVITY;
        Fov = INITIAL_FOV;
        Position = position;
        Yaw = yaw;
        Pitch = pitch;
        NearClip = nearClip;
        FarClip = farClip;
        updateCameraVectors();
        RegenerateProjectionMatrix();
    }

    void UpdateResolution(ivec2 newRes) {
        resolution = newRes;
        RegenerateProjectionMatrix();
    }

    ivec2 GetResolution() {
        return resolution;
    }

    mat4 GetViewMatrix() {
        return viewMatrix;
    }

    mat4 GetProjectionMatrix() {
        return projectionMatrix;
    }

    vec3 GetPosition() {
        return Position;
    }

    void UpdatePosition(vec3 newPos) {
        Position = newPos;
        RegenerateViewMatrix();
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;

        switch (direction) {
            case FORWARD:
                UpdatePosition(Position + (Front * velocity));
                break;
            case BACKWARD:
                UpdatePosition(Position - (Front * velocity));
                break;
            case LEFT:
                UpdatePosition(Position - (Right * velocity));
                break;
            case RIGHT:
                UpdatePosition(Position + (Right * velocity));
                break;
            case UP:
                UpdatePosition(Position + (WorldUp * velocity));
                break;
            case DOWN:
                UpdatePosition(Position - (WorldUp * velocity));
                break;
        }

        RegenerateViewMatrix();
    }

    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) {
        xOffset *= MouseSensitivity;
        yOffset *= MouseSensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        if (constrainPitch) {
            Pitch = clamp(Pitch, -89.0f, 89.0f);
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yOffset) {
        Fov -= yOffset;

        Fov = clamp(Fov, 1.0f, 45.0f);
        RegenerateProjectionMatrix();
    }

private:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    const vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Fov;

    float NearClip;
    float FarClip;

    mat4 viewMatrix;
    mat4 projectionMatrix;

    ivec2 resolution;

    void RegenerateViewMatrix() {
        viewMatrix = lookAt(Position, Position + Front, Up);
    }

    void RegenerateProjectionMatrix() {
        projectionMatrix = perspective(radians(Fov), (float)GetResolution().x / (float)GetResolution().y, NearClip, FarClip);
    }

    void updateCameraVectors() {
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        Right = normalize(cross(Front, WorldUp));
        Up = normalize(cross(Right, Front));
        RegenerateViewMatrix();
    }
};

#endif //OPENGLRAYTRACER_CAMERA_H
