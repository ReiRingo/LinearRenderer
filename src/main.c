#include "linear.h"
#include <stdio.h>


int main(int argc, char* argv[]) {
    lr_window* ex = lin_window_init(640, 480, "Const Char* Name");

    if (!ex) return -1;

    lr_vertex verts[] = {
        // X,      Y,      Z,     U,    V
        { 100.0f, 100.0f, 0.0f,  0.0f, 1.0f }, // top    left  (V was 0.0)
        { 400.0f, 100.0f, 0.0f,  1.0f, 1.0f }, // top    right (V was 0.0)
        { 400.0f, 400.0f, 0.0f,  1.0f, 0.0f }, // bottom right (V was 1.0)
        { 100.0f, 400.0f, 0.0f,  0.0f, 0.0f }  // bottom left  (V was 1.0)
    };
    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 }; // two triangles for a square

    lr_shader shader   = lr_shader_load("shaders/default.vert", "shaders/default.frag");
    lr_mesh   triangle = lr_mesh_create(verts, 4, indices, 6);

    // load the texture (madobe nanami)
    lr_texture my_tex = lr_texture_load("assets/test_image.png");

    while(!lr_window_should_close(ex)) {
        glClear(GL_COLOR_BUFFER_BIT);

        lr_shader_use(shader);
        
        mat4 projection;
        glm_ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f, projection);

        int proj_loc = glGetUniformLocation(shader.id, "u_projection");
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (float*)projection);

        // bind texture 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, my_tex.id);
        
        lr_mesh_draw(triangle);

        lr_window_poll(ex);
    }

    lin_window_close();

    return 0;
}