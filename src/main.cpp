#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include"shaderClass.h"


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
    float vertices[] = {
            -0.5f, -0.5f, 0.0,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };


    // initialize Vertex Buffer Object pointer and generate actual buffer 
    GLuint VBO;
    glGenBuffers(1, &VBO);


    // bind the created Vertex Buffer Object to the actual opengl buffer to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // actually bind vertices data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    // create shader program

    Shader shaderProgram("src/shaders/basic.vert", "src/shaders/basic.frag");

    // main loop
    while (!glfwWindowShouldClose(win)) {


        // read input press keyboard
        processInput(win);


        // fill the canvas with color
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // create the vertex attribute pointer for 3 vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
        glEnableVertexAttribArray(0);


        unsigned int VAO;
        glGenVertexArrays(1, &VAO);


        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(0, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

        glEnableVertexAttribArray(0);


        shaderProgram.Activate();

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
}
