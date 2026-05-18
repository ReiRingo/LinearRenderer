#include "window.h"
#include <stdlib.h>

// window.h definitions

lr_window* lr_window_create(int width, int height, const char* caption) {
    lr_window* win = malloc(sizeof(lr_window));

    // * GLFW hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win->handle = glfwCreateWindow(width, height, caption, 0, 0);
    if (!win->handle) {
        free(win);
        return NULL;
    }

    // * Assign metadata
    win->width   = width;
    win->height  = height;
    win->caption = caption;

    glfwMakeContextCurrent(win->handle);
    return win;
}

int lr_window_should_close(lr_window* win) {
    return glfwWindowShouldClose(win->handle);
}

void lr_window_poll(lr_window* win) {
    glfwPollEvents();
    glfwSwapBuffers(win->handle);
    
    glfwGetWindowSize(win->handle, &win->width, &win->height);
    
    int fb_w, fb_h;
    glfwGetFramebufferSize(win->handle, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);
}

void lr_window_destroy(lr_window* win) {
    glfwDestroyWindow(win->handle);
    free(win);
}