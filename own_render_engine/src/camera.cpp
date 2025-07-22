#include"CameraClass.h"


double scrollY = 0.0;

void scroll_cb(GLFWwindow*, double /*xoff*/, double yoff)
{
    scrollY += yoff;
}

Camera::Camera(int width, int height, glm::vec3 pos){
    Camera::width = width;
    Camera::height = height;
    Position = pos;

    recalcOrientation();   
    Up = glm::vec3(0.0f, 1.0f,  0.0f);
}

void Camera::Matrix(float fov_deg, float near_plane, float far_plane, Shader& shader, const char* uniform){
    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 proj = glm::mat4(1.0f);

    Camera::fov_deg = fov_deg;

    view = glm::lookAt(Position, Position + Orientation, Up);

    proj = glm::perspective(glm::radians(fov_deg), float(width) / float(height), near_plane, far_plane);

    int matrix_ptr;

    matrix_ptr = glGetUniformLocation(shader.ID, uniform);
    glUniformMatrix4fv(matrix_ptr, 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* win){
    // std::cout << glm::to_string(pivot) << '\n';

    glfwSetWindowUserPointer(win, this);
    glfwSetScrollCallback(win, scroll_cb);

    std::cout << scrollY << "\n";

    // move pivot

    // is ctrl holded
    bool ctrl_hold = glfwGetKey(win, GLFW_KEY_LEFT_CONTROL);

    bool alt_hold = glfwGetKey(win, GLFW_KEY_LEFT_ALT);

    bool shift_hold = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);

    double curX, curY, dx, dy, dScroll;

    glfwGetCursorPos(win, &curX, &curY);

    if (first_frame){
        first_frame = false;
    }
    else{
        dx = curX - lastX;
        dy = curY - lastY;

        std::cout << "scrollY " << scrollY << "\n" << "lastScroll " << lastScroll << "\n" << "------------------------------------------- \n";

        dScroll = scrollY - lastScroll;

        std::cout << "dScroll " << dScroll << "\n";

        // std::cout << "x " << dx << " |    y " << dy << "\n";
    }

    lastX = curX;
    lastY = curY;
    lastScroll = scrollY;



    // pan view
    if (ctrl_hold){

        std::cout << "ctrl_pressed \n";


        // 1.1 get the normal to the pivot plane (Orientation)

        // 1.2 get the direction vector of u_0 projected along the plane normal  
        glm::vec3 u;

        u = glm::normalize(Up - glm::dot(Up, Orientation) * Orientation);

        // this u in k is the first basis vector of K
        // we could make pivot + u to get the actual basis vector in K.

        // 1.3 now we need to find second vector r which should be orthogonal to n and u
        // these could be done using cross product r = u X n

        glm::vec3 r;

        r = glm::cross(u, Orientation);

        // now we have the orthogonal basis is K


        // 2 in next phase we need to map screen coordinates (s, t) to the world coordinates

        // 2.1 forward mapping dP = dx * r + dy * u

        glm::vec3 dPivot;

        dPivot = r * static_cast<float>(dx) + u * static_cast<float>(dy);
        
        std::cout << glm::to_string(dPivot) << '\n';

        pivot += speed * dPivot;
    }


    // zoom in/out
    distance -= zoomSpeed * dScroll;


    // rotate around pivot

    if (alt_hold){
        yaw -= dx * static_cast<float>(sensitivity);
        pitch += dy * static_cast<float>(sensitivity);

        const float lim = glm::radians(89.0f);
        pitch = glm::clamp(pitch, -lim, lim);
    }


    Position.x = pivot.x + distance * cos(pitch)*sin(yaw);
    Position.y = pivot.y + distance * sin(pitch);
    Position.z = pivot.z + distance * cos(pitch)*cos(yaw);

    recalcOrientation();

}