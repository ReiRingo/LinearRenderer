#include "mesh.h"

lr_mesh lr_mesh_create(lr_vertex* vertices, int v_count, unsigned int* indices, int i_count) {
    lr_mesh mesh;
    mesh.index_count = i_count;

    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    glBindVertexArray(mesh.vao);

    // upload vertex data 1
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(lr_vertex), vertices, GL_STATIC_DRAW);

    // upload vertex data 2
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // define layout (location 0 in our shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(lr_vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // ------
    // from what i learned online
    // this is defining the layout for the texcoord (location 1 in the shader)
    // sizeof lr_vertx is the distance to the next vertex's uv? - correct me if im wrong
    // (void*)(3 * sizeof(float)) is the offset (skip the 3 position floats) - once again, scold me
    // ------
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(lr_vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // unbined to stay clean
    return mesh;
}

void lr_mesh_draw(lr_mesh mesh) {
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
}