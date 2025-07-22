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

        void LinkAttrib(VBO& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset);
        
        void Bind();

        void Unbind();

        void Delete();
};


#endif