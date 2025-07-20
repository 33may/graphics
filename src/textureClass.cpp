#include"TextureObjectClass.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


unsigned char* LoadImageFile(const char* path, int* width_img_ptr, int* heigth_img_ptr, int* col_channels_img_ptr){
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(path, width_img_ptr, heigth_img_ptr, col_channels_img_ptr, 0);

    return bytes;
}


Texture::Texture(){
    glGenTextures(1, &ID);
    
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void Texture::LoadImage(Shader& shaderProgram, const char* path){

    int width_img, heigth_img, col_channels_img;

    unsigned char* bytes;

    bytes = LoadImageFile(path, &width_img, &heigth_img, &col_channels_img);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_img, heigth_img, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    shaderProgram.Activate();
    GLuint tex0_uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    glUniform1i(tex0_uni, 0);
    
    stbi_image_free(bytes);
}



void Texture::Bind(){
    glBindTexture(GL_ARRAY_BUFFER, ID);
}

void Texture::Unbind(){
    glBindTexture(GL_ARRAY_BUFFER, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);

}