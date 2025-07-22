#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include"shaderClass.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream> 

class Camera{
    public:
        glm::vec3 Position;
        glm::vec3 Orientation;
        glm::vec3 Up;

        int height;
        int width;

        float fov_deg;

        float speed = 1e-2f;
        float zoomSpeed = 5e-1f;
        float sensitivity = 0.01f;

        glm::vec3 pivot = glm::vec3(0.0f, 0.0f, 0.0f);
        float distance = 5;
        float yaw = 0, pitch = 0;

        double lastX, lastY, lastScroll;

        bool first_frame = true;

        void recalcOrientation() {
            Orientation = glm::normalize(pivot - Position);
        }
        
        Camera(int height, int width, glm::vec3 pos);

        void Matrix(float fov_deg, float near_plane, float far_plane, Shader& shader, const char* uniform);

        void Inputs(GLFWwindow* win);
};

#endif