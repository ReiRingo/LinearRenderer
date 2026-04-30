#include "linear.h"

static lr_window* _LIN_WINDOW_GLOBAL   = (lr_window*)NULL;
static bool       _LIN_HAS_INIT_WINDOW = false;

lr_window* lin_window_init(int width, int height, const char* caption) {
    if (!_LIN_HAS_INIT_WINDOW) {
        if (!glfwInit()) {
            printf("FAILED TO INITIALISE GLFW\n");
            return NULL;
        }

        _LIN_WINDOW_GLOBAL = lr_window_create(width, height, caption);

        if (!_LIN_WINDOW_GLOBAL) {
            printf("FAILED TO INITIALISE MAIN LINEAR WINDOW");
            return NULL;
        }

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            printf("FAILED TO INITIALISE GLAD\n");
            return NULL;
        }

        glViewport(0, 0, width, height);

        _LIN_HAS_INIT_WINDOW = true;
    } else {
        printf("WINDOW ALREADY INITIALISED :: Use lr_window_create() for new\nwindow initialisations.");
    }

    return _LIN_WINDOW_GLOBAL;
}