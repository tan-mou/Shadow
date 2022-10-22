#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;
class Camera
{

private:
    glm::vec3 cameraPos ;
    glm::vec3 cameraTarget ;
    glm::vec3 cameraDirection ;
    glm::vec3 cameraUp ;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;
public:
    Camera(glm::vec3 pos,glm::vec3 direction,glm::vec3 up) {
        cameraPos = pos;
        cameraDirection = direction;
        cameraUp = up;
        cameraTarget = cameraPos + cameraDirection;
        Yaw = YAW;
        Pitch = PITCH;
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Fov = FOV;
    }

    glm::mat4 GetView() {
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
        return view;
    }
    glm::vec3 GetPos() {
        return cameraPos;
    }
    glm::vec3 GetDir() {
        return cameraDirection;
    }
    glm::vec3 GetUp() {
        return cameraUp;
    }

    void Set_Keyborad_MOVE(float deltatime,unsigned int keyword) {
        if(keyword== GLFW_KEY_W)
            cameraPos+=SPEED*deltatime*cameraDirection;
        if (keyword == GLFW_KEY_S)
            cameraPos -= SPEED * deltatime * cameraDirection;
        if (keyword == GLFW_KEY_A)
            cameraPos -= SPEED * deltatime * glm::normalize((glm::cross(cameraDirection,cameraUp)));
        if (keyword == GLFW_KEY_D)
            cameraPos += SPEED * deltatime * glm::normalize((glm::cross(cameraDirection, cameraUp)));

        if (keyword == GLFW_KEY_SPACE)
            cameraPos += SPEED * deltatime * glm::vec3(0.0f, 1.0f, 0.0f);
        if (keyword == GLFW_KEY_LEFT_CONTROL)
            cameraPos -= SPEED * deltatime * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    void Set_Mouse_MOVE(float xoffset,float yoffset) {
        Pitch += yoffset;
        Yaw += xoffset;
        if (Pitch > 90)
            Pitch = 89.0f;
        if (Pitch < -90)
            Pitch = -89.0f;


        cameraDirection.x = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));


        cameraDirection.y = sin(glm::radians(Pitch));

        cameraDirection.z = -cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        cameraDirection = glm::normalize(cameraDirection);
    }





};

