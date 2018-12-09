#include "Camera.h"

Camera::Camera(glm::vec3 position) :
        position(position),
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        worldUp(up),
        yaw(YAW),
        pitch(PITCH),
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVTY),
        zoom(ZOOM) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD) {
        position.x += front.x * velocity;
        position.z += front.z * velocity;
    }
    if (direction == CameraMovement::BACKWARD) {
        position.x -= front.x * velocity;
        position.z -= front.z * velocity;
    }
    if (direction == CameraMovement::LEFT) {
        position -= right * velocity;
    }
    if (direction == CameraMovement::RIGHT) {
        position += right * velocity;
    }
    if (direction == CameraMovement::UP) {
        position.y += velocity;
    }
    if (direction == CameraMovement::DOWN) {
        position.y -= velocity;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset,
        bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(const float yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 frontNew;
    frontNew.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontNew.y = sin(glm::radians(pitch));
    frontNew.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontNew);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

