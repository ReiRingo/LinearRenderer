#ifndef  LR_SHADER
# define LR_SHADER "0.0.1"

typedef struct {
    unsigned int id;
} lr_shader;

lr_shader  lr_shader_load(const char* vert_path, const char* frag_path);
void       lr_shader_use(lr_shader shd);

#endif