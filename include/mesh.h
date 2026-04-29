#ifndef  LR_MESH
# define LR_MESH "0.0.1"

#include <glad/glad.h>

typedef struct {
    float x, y, z;
} lr_vertex_t;

typedef struct {
    unsigned int vao, vbo, ebo;
    unsigned int index_count;
} lr_mesh_t;

lr_mesh_t lr_mesh_create(lr_vertex_t* vertices, int v_count, unsigned int* indices, int i_count);
void      lr_mesh_draw(lr_mesh_t mesh);
void      lr_mesh_destroy(lr_mesh_t mesh);

#endif