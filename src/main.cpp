#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VertexBufferClass.h"
#include"VertexAttributeObject.h"
#include"ElementBufferObject.h"
#include"TextureObjectClass.h"


struct WindowSize {
    int width;
    int height;
};


// function to modify glfwWindow on resize
void framebuffer_size_callback(GLFWwindow* win, int width, int heigth){
    glViewport(0, 0, width, heigth);

    auto* ws = static_cast<WindowSize*>(glfwGetWindowUserPointer(win));

    ws->width = width;
    ws->height = heigth;

    // std::cout << "W: "<< width << "\n H: " << heigth;
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


    WindowSize size(600, 800);


    // create the window and save pointer for it 
    GLFWwindow* win = glfwCreateWindow(size.width, size.height, "Hello World", nullptr, nullptr);
    if (!win) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(win, &size);


    // make context current, activate created window
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);               // V‑sync


    // load opengl code implementation
    if (!gladLoadGL(glfwGetProcAddress)){
        std::cerr << "glad loader Failed \n";
        return -1;
    }

    // set viewport to match the windowsize
    glViewport(0, 0, size.width, size.height);


    // add the created size adjust function to the window callback
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);


    // // create verticies of triangle with their coloors
    // GLfloat vertices[] = {
    //         // Position                 Color               // UV Coordinates
    //         -1.0f,    -1.0f,   -1.0f,    0.8f, 0.3f, 0.2f,   0.0f, 0.0f,  // left in bot
    //         -1.0f,     -1.0f,   1.0f,    0.8f, 0.3f, 0.2f,   1.0f, 0.0f,  // left in top
    //         -1.0f,    1.0f,    -1.0f,    1.0f, 0.6f, 0.3f,   0.0f, 1.0f,  // left out bot
    //         -1.0f,    1.0f,    1.0f,    1.0f, 0.6f, 0.3f,    1.0f, 1.0f,  // left out top
    //         1.0f,     -1.0f,   -1.0f,    0.9f, 0.45f, 0.17f, 0.0f, 1.0f,   // right in bot
    //         1.0f,     -1.0f,   1.0f,    0.9f, 0.45f, 0.17f,  1.0f, 1.0f,   // right in top
    //         1.0f,     1.0f,   -1.0f,    0.9f, 0.45f, 0.17f,  0.0f, 0.0f,   // right out bot
    //         1.0f,     1.0f,   1.0f,    0.9f, 0.45f, 0.17f,   1.0f, 0.0f,   // right out top

    //     };

    // // create indices for the shader to know the order to use vertices in buffer
    // GLuint idx[] = {
    //         0, 1, 3,
    //         0, 2, 3,
    //         3, 2, 7,
    //         7, 2, 6,
    //         1, 3, 7,
    //         1, 5, 7,
    //         7, 5, 6,
    //         4, 5, 6,
    //         2, 6, 4,
    //         0, 2, 4,
    //         0, 4, 5,
    //         1, 0, 5,

    //     };



    GLfloat vertices[] = {
    // ─ front (+Z)
    -1,-1, 1,  .8,.3,.2,  0,0,
    1,-1, 1,  .8,.3,.2,  1,0,
    1, 1, 1,  1,.6,.3,  1,1,
    -1, 1, 1,  1,.6,.3,  0,1,
    // ─ back (−Z)
    1,-1,-1,  .9,.45,.17, 0,0,
    -1,-1,-1,  .9,.45,.17, 1,0,
    -1, 1,-1,  .9,.45,.17, 1,1,
    1, 1,-1,  .9,.45,.17, 0,1,
    // ─ left (−X)
    -1,-1,-1,  .8,.3,.2,  0,0,
    -1,-1, 1,  .8,.3,.2,  1,0,
    -1, 1, 1,  1,.6,.3,  1,1,
    -1, 1,-1,  1,.6,.3,  0,1,
    // ─ right (+X)
    1,-1, 1,  .9,.45,.17, 0,0,
    1,-1,-1,  .9,.45,.17, 1,0,
    1, 1,-1,  .9,.45,.17, 1,1,
    1, 1, 1,  .9,.45,.17, 0,1,
    // ─ top (+Y)
    -1, 1, 1,  .8,.3,.2,  0,0,
    1, 1, 1,  .8,.3,.2,  1,0,
    1, 1,-1,  1,.6,.3,  1,1,
    -1, 1,-1,  1,.6,.3,  0,1,
    // ─ bottom (−Y)
    -1,-1,-1,  .9,.45,.17, 0,0,
    1,-1,-1,  .9,.45,.17, 1,0,
    1,-1, 1,  .9,.45,.17, 1,1,
    -1,-1, 1,  .9,.45,.17, 0,1
    };


    GLuint idx[] = {
    0, 1, 2,  2, 3, 0,        // front
    4, 5, 6,  6, 7, 4,        // back
    8, 9,10, 10,11, 8,        // left
    12,13,14, 14,15,12,        // right
    16,17,18, 18,19,16,        // top
    20,21,22, 22,23,20         // bottom
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

    float rotation = 0.0f;
    double prevTime = glfwGetTime();


    glEnable(GL_DEPTH_TEST);

    // main loop
    while (!glfwWindowShouldClose(win)) {

        // read input press keyboard
        processInput(win);


        // fill the canvas with color
        glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        double crnt_time = glfwGetTime();

        if (crnt_time - prevTime > 1/60){
            rotation += 0.5f;
            prevTime = crnt_time;
        } 

        // std::cout << "W: "<< size.width << "\n H: " << size.height;

        glm::mat4 model = glm::mat4(1.0f);
        
        glm::mat4 view = glm::mat4(1.0f);

        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        view = glm::translate(view, glm::vec3(0.0f, -0.1f, -3.0f));

        view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        proj = glm::perspective(glm::radians(45.0f), float(size.width) / float(size.height), 0.1f, 100.0f);


        int model_ptr, view_ptr, proj_ptr;

        model_ptr = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(model_ptr, 1, GL_FALSE, glm::value_ptr(model));

        view_ptr = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(view_ptr, 1, GL_FALSE, glm::value_ptr(view));

        proj_ptr = glGetUniformLocation(shaderProgram.ID, "proj");    
        glUniformMatrix4fv(proj_ptr, 1, GL_FALSE, glm::value_ptr(proj));


        glUniform1f(uniform_scale_ptr, 0.5f);

        texture.Bind();
        
        vao.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(idx) / sizeof(int), GL_UNSIGNED_INT, 0);

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
