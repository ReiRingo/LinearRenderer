#ifndef LR_TEXTURE
#define LR_TEXTURE "0.0.1"

typedef struct {
    unsigned int id;
    int width,
        height,
        channels;
} lr_texture;

lr_texture lr_texture_load(const char* path);

#endif