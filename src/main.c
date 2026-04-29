#include "window.h"
#include "shader.h"
#include "mesh.h"
#include <stdio.h>

static inline lr_window_t* window_start() {
    if (!glfwInit()) {
        printf("FAILED TO INITIALISE GLFW\n");
        return NULL;
    }

    lr_window_t* example = lr_window_create(640, 480, "Test");

    if (!example) {
        printf("FAILED TO CREATE WINDOW\n");
        return NULL;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("FAILED TO INITIALISE GLAD\n");
        return NULL;
    }

    glViewport(0, 0, 640, 480);

    return example;
}

int main(int argc, char* argv[]) {
    lr_window_t* ex = window_start();

    if (!ex) return -1;

    lr_vertex_t verts[] = {
        {-0.5f, -0.5f,  0.0f}, // bottom left
        { 0.5f, -0.5f,  0.0f}, // bottom right
        { 0.0f,  0.5f,  0.0f}  // top center
    };
    unsigned int indices[] = { 0, 1, 2 };

    lr_shader_t shader   = lr_shader_load("shaders/default.vert", "shaders/default.frag");
    lr_mesh_t   triangle = lr_mesh_create(verts, 3, indices, 3);
    
    while(!lr_window_should_close(ex)) {
        // Render stuff
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        lr_shader_use(shader);
        lr_mesh_draw(triangle);

        // Swap and Poll
        lr_window_poll(ex);
    }

    lr_window_destroy(ex);
    glfwTerminate();

    return 0;
}