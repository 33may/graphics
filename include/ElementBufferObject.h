#ifndef ELEMENT_OBJECT_CLASS
#define ELEMENT_OBJECT_CLASS

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>


class EBO{
    public:
        GLuint ID;
        EBO(GLuint* idx, GLsizeiptr size);
        
        void Bind();

        void Unbind();

        void Delete();
};


#endif