#ifndef VERTEX_ATTRIBUTE_CLASS
#define VERTEX_ATTRIBUTE_CLASS

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include"VertexBufferClass.h"


class VAO{
    public:
        GLuint ID;
        VAO();

        void LinkVBO(VBO vbo, GLuint layout);
        
        void Bind();

        void Unbind();

        void Delete();
};


#endif