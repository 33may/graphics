#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    // 6. Главный цикл
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();              // события ввода

        glClearColor(0.0f, 0.2f, 0.4f, 1.0f); // заливаем фон
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win);          // commit кадра → окно станет видимым
    }

    // 7. Завершаем работу
    glfwDestroyWindow(win);
    glfwTerminate();
}
