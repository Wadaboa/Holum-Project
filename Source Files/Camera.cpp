//
//
//  Project : Holum
//  File Name : Camera.cpp
//  Date : 08/02/2016
//
//

#include <Global.h>
#include <Camera.h>

Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch) : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM), minZoom(ZOOM - 1), maxZoom(zoom + 1) {
    this->position = position;
    worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM) {
    position = vec3(posX, posY, posZ);
    worldUp = vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

mat4 Camera::GetViewMatrix() {
    return lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if(constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
    if (yoffset < 0) {
        yoffset = 0.1f;
    }
    else {
        yoffset = -0.1f;
    }
    if (zoom >= minZoom && zoom <= maxZoom)
        zoom -= yoffset;
    if (zoom < minZoom)
        zoom = minZoom;
    if (zoom > maxZoom)
        zoom = maxZoom;
}

void Camera::updateCameraVectors() {
    vec3 front;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    front = normalize(front);
    
    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}

