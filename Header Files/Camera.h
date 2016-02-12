//
//
//  Project : Holum
//  File Name : Camera.h
//  Date : 08/02/2016
//
//

#pragma once

class Camera {
    public:
        typedef enum {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        } Camera_Movement;
        
        constexpr static const GLfloat YAW = -90.0f;
        constexpr static const GLfloat PITCH = 0.0f;
        constexpr static const GLfloat SPEED = 3.0f;
        constexpr static const GLfloat SENSITIVTY = 0.25f;
        constexpr static const GLfloat ZOOM = 45.0f;

        vec3 position;
        vec3 front;
        vec3 up;
        vec3 right;
        vec3 worldUp;
        
        GLfloat yaw;
        GLfloat pitch;
        
        GLfloat movementSpeed;
        GLfloat mouseSensitivity;
        GLfloat zoom;
        GLfloat minZoom;
        GLfloat maxZoom;
    
        Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
        Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
        mat4 GetViewMatrix();
        void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
        void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);
        void ProcessMouseScroll(GLfloat yoffset);

    private:
        void updateCameraVectors();
};