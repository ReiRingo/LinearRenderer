#ifndef  LR_WINDOW
# define LR_WINDOW "0.0.1"

#include <glad/glad.h>
#include <glfw/glfw3.h>

typedef struct s__lr_window {
    GLFWwindow* handle;
    int width,  height;
    const char* caption;
} lr_window;

lr_window*   lr_window_create(int width, int height, const char* caption);
void         lr_window_poll(lr_window* win);
int          lr_window_should_close(lr_window* win);
void         lr_window_destroy(lr_window* win);

#endif