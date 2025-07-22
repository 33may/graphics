#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include"shaderClass.h"

unsigned char* LoadImageFile(const char* path, int* width_img_ptr, int* heigth_img_ptr, int* col_channels_img_ptr);

class Texture{
    public:
        GLuint ID;

        Texture();

        void LoadImage(Shader& shaderProgram, const char* path);

        void Bind();

        void Unbind();

        void Delete();
};

#endif