#include "linear.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
    lr_window* ex = lin_window_init(640, 480, "Const Char* Name");

    if (!ex) return -1;

    // updated Vertices (X, Y, Z, U, V)
    lr_vertex verts[] = {
        {-0.5f, -0.5f, 0.0f,  0.0f, 0.0f }, // Bottom Left
        { 0.5f, -0.5f, 0.0f,  1.0f, 0.0f }, // Bottom Right
        { 0.5f,  0.5f, 0.0f,  1.0f, 1.0f }, // Top Right
        {-0.5f,  0.5f, 0.0f,  0.0f, 1.0f }  // Top Left
    };
    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 }; // two triangles for a square

    lr_shader shader   = lr_shader_load("shaders/default.vert", "shaders/default.frag");
    lr_mesh   triangle = lr_mesh_create(verts, 4, indices, 6);

    // load the texture (madobe nanami)
    lr_texture my_tex = lr_texture_load("assets/test_image.png");

    while(!lr_window_should_close(ex)) {
        glClear(GL_COLOR_BUFFER_BIT);

        lr_shader_use(shader);
        
        // bind texture 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, my_tex.id);
        
        lr_mesh_draw(triangle);

        lr_window_poll(ex);
    }

    lr_window_destroy(ex);
    glfwTerminate();

    return 0;
}