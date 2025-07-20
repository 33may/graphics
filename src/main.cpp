#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include"shaderClass.h"
#include"VertexBufferClass.h"
#include"VertexAttributeObject.h"
#include"ElementBufferObject.h"
#include"TextureObjectClass.h"


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


    // create verticies of triangle with their coloors
    GLfloat vertices[] = {
            // Position                 Color               // UV Coordinates
            -1.0f,    -1.0f,   0.0f,    0.8f, 0.3f, 0.2f,   0.0f, 0.0f,  // lower left corner
            1.0f,     -1.0f,   0.0f,    0.8f, 0.3f, 0.2f,   1.0f, 0.0f,  // lower riht corner
            -1.0f,    1.0f,    0.0f,    1.0f, 0.6f, 0.3f,   0.0f, 1.0f,  // upper left corner
            1.0f,     1.0f,    0.0f,    0.9f, 0.45f, 0.17f, 1.0f, 1.0f   // upper right corner

        };

    // create indices for the shader to know the order to use vertices in buffer
    GLuint idx[] = {
            0, 1, 2,
            1, 2, 3,
        };


    // create shader program

    Shader shaderProgram("src/shaders/basic.vert", "src/shaders/basic.frag");
    

    // VAO is general rule of where to get and how to use vertices from the GPU buffers
    VAO vao;

    vao.Bind();

    // VBO is responsible for storring raw data in buffer on GPU
    VBO vbo(vertices, sizeof(vertices));
    
    // EBO is rule about the order of using verticies in data. Rule how to form meshes from vertices
    EBO ebo(idx, sizeof(idx));
    
    // link position attribute
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);

    // link collor attribute
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    GLuint uniform_scale_ptr = glGetUniformLocation(shaderProgram.ID, "scale");

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    // create texture

    Texture texture;

    texture.LoadImage(shaderProgram, "src/textures/orangutan.jpeg");

    texture.Unbind();

    // main loop
    while (!glfwWindowShouldClose(win)) {


        // read input press keyboard
        processInput(win);


        // fill the canvas with color
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        glUniform1f(uniform_scale_ptr, 0.7f);

        texture.Bind();
        
        vao.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(win);
    }


    vbo.Delete();
    vao.Delete();
    ebo.Delete();
    texture.Delete();

    shaderProgram.Delete();
    glfwDestroyWindow(win);
    glfwTerminate();
}
