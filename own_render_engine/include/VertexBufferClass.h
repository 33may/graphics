#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

class VBO{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();

        void Unbind();

        void Delete();
};

#endif