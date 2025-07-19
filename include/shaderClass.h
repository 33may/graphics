#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

std::string loadFileSrc(const char* path);

class Shader{
    public:
        GLuint ID;
        Shader(const char* vertextFilePath, const char* fragmentFilePath);

        void Activate();

        void Delete();
};

#endif