#ifndef  LR_MESH
# define LR_MESH "0.0.1"

#include <glad/glad.h>

typedef struct {
    float x, y, z;
    float u, v;
} lr_vertex;

typedef struct {
    unsigned int vao, vbo, ebo;
    unsigned int index_count;
} lr_mesh;

lr_mesh   lr_mesh_create(lr_vertex* vertices, int v_count, unsigned int* indices, int i_count);
void      lr_mesh_draw(lr_mesh mesh);
void      lr_mesh_destroy(lr_mesh mesh);

#endif