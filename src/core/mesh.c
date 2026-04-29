#include "mesh.h"

lr_mesh_t lr_mesh_create(lr_vertex_t* vertices, int v_count, unsigned int* indices, int i_count) {
    lr_mesh_t mesh;
    mesh.index_count = i_count;

    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    glBindVertexArray(mesh.vao);

    // upload vertex data 1
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(lr_vertex_t), vertices, GL_STATIC_DRAW);

    // upload vertex data 2
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // define layout (location 0 in our shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lr_vertex_t), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // unbined to stay clean
    return mesh;
}

void lr_mesh_draw(lr_mesh_t mesh) {
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
}