#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include"shaderClass.h"
#include"VertexBufferClass.h"
#include"VertexAttributeObject.h"
#include"ElementBufferObject.h"


// function to modify glfwWindow on resize
void framebuffer_size_callback(GLFWwindow* win, int width, int heigth){
    glViewport(0, 0, width, heigth);

    std::cout << "W: "<< width << "\n H: " << heigth;
}


// process esc input
void processInput(GLFWwindow* win){
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(win, true);
    }
}


int main() {

    // configure wayland window manager
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

    // initialize glfw window manager
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return -1;
    }


    // configure glfw version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // create the window and save pointer for it 
    GLFWwindow* win = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!win) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }


    // make context current, activate created window
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);               // V‑sync


    // load opengl code implementation
    if (!gladLoadGL(glfwGetProcAddress)){
        std::cerr << "glad loader Failed \n";
        return -1;
    }

    // set viewport to match the windowsize
    glViewport(0, 0, 640, 480);


    // add the created size adjust function to the window callback
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);


    // create verticies of triangle
    GLfloat vertices[] = {
            -0.5f, -0.5f * float(std::sqrt(3)) / 3, 0.0f,
            0.5f, -0.5f * float(std::sqrt(3)) / 3, 0.0f,
            0.0f, 0.5f * float(std::sqrt(3)) * 2 / 3, 0.0f,
            -0.5f / 2,  0.5f * float(std::sqrt(3)) / 6, 0.0f,
            0.5f / 2,  0.5f * float(std::sqrt(3)) / 6, 0.0f,
            0.0f,  -0.5f * float(std::sqrt(3)) / 3, 0.0f,
        };

    GLuint idx[] = {
            0, 3, 5,
            3, 2, 4,
            5, 4, 1
        };


    // create shader program

    Shader shaderProgram("src/shaders/basic.vert", "src/shaders/basic.frag");
    
    // VBO is responsible for storring the data in buffer on GPU
    
    VAO vao;

    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));

    EBO ebo(idx, sizeof(idx));

    vao.LinkVBO(vbo, 0);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // main loop
    while (!glfwWindowShouldClose(win)) {


        // read input press keyboard
        processInput(win);


        // fill the canvas with color
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        
        vao.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(win);
    }


    vbo.Delete();
    vao.Delete();
    ebo.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(win);
    glfwTerminate();
}
