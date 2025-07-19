#include"VertexBufferClass.h"

VBO::VBO(GLfloat* vertices){
    // initialize Vertex Buffer Object pointer and generate actual buffer 
    glGenBuffers(1, &ID);

    // bind the created Vertex Buffer Object to the actual opengl buffer to use
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    // actually bind vertices data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}