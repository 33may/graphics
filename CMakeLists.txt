cmake_minimum_required(VERSION 3.30)
project(graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(external/glad)

add_executable(graphics
               src/main.cpp
               src/shader.cpp
               src/vbo.cpp
               src/vao.cpp
               src/ebo.cpp
               src/textureClass.cpp)

target_link_libraries(graphics PRIVATE glad glfw OpenGL::GL glm::glm)
target_include_directories(graphics PRIVATE ${PROJECT_SOURCE_DIR}external/glad/include)
target_include_directories(graphics PRIVATE ${PROJECT_SOURCE_DIR}/external/stb)

target_include_directories(graphics PRIVATE include)

