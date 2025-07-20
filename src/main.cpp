#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

    int width_img, heigth_img, col_channels_img;

    unsigned char* bytes = stbi_load("src/textures/orangutan.jpeg", &width_img, &heigth_img, &col_channels_img, 0);

    // std::cout << col_channels_img << std::endl;
    
    GLuint texture;
    
    glGenTextures(1, &texture);
    
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_img, heigth_img, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLuint tex0_uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0_uni, 0);
    
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    // main loop
    while (!glfwWindowShouldClose(win)) {


        // read input press keyboard
        processInput(win);


        // fill the canvas with color
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        glUniform1f(uniform_scale_ptr, 0.7f);

        glBindTexture(GL_TEXTURE_2D, texture);
        
        vao.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(win);
    }


    vbo.Delete();
    vao.Delete();
    ebo.Delete();

    glDeleteTextures(1, &texture);

    shaderProgram.Delete();
    glfwDestroyWindow(win);
    glfwTerminate();
}
