#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* win, int width, int heigth){
    glViewport(0, 0, width, heigth);

    std::cout << "W: "<< width << "\n H: " << heigth;
}

void processInput(GLFWwindow* win){
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(win, true);
    }
}

std::string loadFileSrc(const char* path){
    std::ifstream in(path, std::ios::binary);

    if (!in) {
        std::perror(path);
        return {};
    }

    return std::string((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
}


int main() {
    // 1. Сначала выбираем бэкенд Wayland
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);

    // 2. Инициализируем GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return -1;
    }

    // 3. Просим Core‑контекст 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 4. Создаём окно
    GLFWwindow* win = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!win) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    // 5. Делаем контекст текущим
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);               // V‑sync

    if (!gladLoadGL(glfwGetProcAddress)){
        std::cerr << "glad loader Failed \n";
        return -1;
    }

    glViewport(0, 0, 640, 480);

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

    // 6. Главный цикл
    while (!glfwWindowShouldClose(win)) {

        // input
        processInput(win);


        // render commands

        glClearColor(0.0f, 0.2f, 0.4f, 1.0f); // заливаем фон

        glClear(GL_COLOR_BUFFER_BIT);

        // vertices

        float vertices[] = {
            -0.5f, -0.5f, 0.0,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };


        // array buffer

        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // copy the vertices to VBO buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        // vertex shader

        std::string vertexSrc = loadFileSrc("src/shaders/basic.vert");
        std::string fragmentSrc = loadFileSrc("src/shaders/basic.frag");

        // std::cout << vertexSrc;

        const GLchar* srcVertexPtr = vertexSrc.c_str();
        const GLchar* srcFragmentPtr = fragmentSrc.c_str();

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &srcVertexPtr, nullptr);

        glCompileShader(vertexShader);
        


        // fragment shader

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &srcFragmentPtr, nullptr);

        glCompileShader(fragmentShader);



        // shader program

        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();


        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // set the vertex attribute pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
        glEnableVertexAttribArray(0);


        unsigned int VAO;
        glGenVertexArrays(1, &VAO);


        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(0, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

        glEnableVertexAttribArray(0);


        // draw the object 
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap buffer

        glfwPollEvents();              // события ввода
        glfwSwapBuffers(win);          // commit кадра → окно станет видимым
    }

    // 7. Завершаем работу
    glfwDestroyWindow(win);
    glfwTerminate();
}
