#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdbool.h>

lr_texture lr_texture_load(const char* path) {
    lr_texture tex = {0};
    stbi_set_flip_vertically_on_load(false); 
    
    unsigned char* data = stbi_load(path, &tex.width, &tex.height, &tex.channels, 0);
    if (data) {
        glGenTextures(1, &tex.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (tex.channels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, tex.width, tex.height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        printf("lr_texture_load :: ERROR, cannot load file %s!\n", path);
    }
    
    return tex;
}