#include "linear.h"

static lr_window *_LIN_WINDOW = (lr_window *)NULL;
static bool _LIN_HAS_INIT_WINDOW = false;
static lr_shader _CUR_SHADER;

lr_window *lin_window_init(int width, int height, const char *caption) {
  if (!_LIN_HAS_INIT_WINDOW) {
    if (!glfwInit()) {
      printf("FAILED TO INITIALISE GLFW\n");
      return NULL;
    }

    _LIN_WINDOW = lr_window_create(width, height, caption);

    if (!_LIN_WINDOW) {
      printf("FAILED TO INITIALISE MAIN LINEAR WINDOW");
      return NULL;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      printf("FAILED TO INITIALISE GLAD\n");
      return NULL;
    }

    int fb_w, fb_h;
    glfwGetFramebufferSize(_LIN_WINDOW->handle, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _LIN_HAS_INIT_WINDOW = true;
  } else {
    printf("WINDOW ALREADY INITIALISED :: Use lr_window_create() for "
           "new\nwindow initialisations.");
  }

  return _LIN_WINDOW;
}

bool lin_window_close() {
  lr_window_destroy(_LIN_WINDOW);
  glfwTerminate();
}

void lin_draw_begin() { glClear(GL_COLOR_BUFFER_BIT); }

void lin_draw_end() {
  if (_LIN_WINDOW) {
    lr_window_poll(_LIN_WINDOW);
  }
}

void lin_use_shader(lr_shader shader) {
  lr_shader_use(shader);
  _CUR_SHADER = shader;

  if (_LIN_WINDOW) {
    mat4 projection;
    glm_ortho(0.0f, (float)_LIN_WINDOW->width, (float)_LIN_WINDOW->height, 0.0f,
              -1.0f, 1.0f, projection);
    int proj_loc = glGetUniformLocation(shader.id, "u_projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, (float *)projection);

    // Reset model matrix to identity for raw geometry
    mat4 model;
    glm_mat4_identity(model);
    int model_loc = glGetUniformLocation(shader.id, "u_model");
    if (model_loc != -1) {
      glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float *)model);
    }
  }
}

lin_sprite lin_sprite_create(const char *image_path) {
  lin_sprite spr = {0};

  spr.tex = lr_texture_load(image_path);

  // We create a 1x1 quad mesh. It will be scaled by the texture's native
  // dimensions and the sprite's scale.
  lr_vertex verts[] = {
      // X,      Y,      Z,     U,    V
      {0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // top    left
      {1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // top    right
      {1.0f, 1.0f, 0.0f, 1.0f, 1.0f}, // bottom right
      {0.0f, 1.0f, 0.0f, 0.0f, 1.0f}  // bottom left
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  spr.mesh = lr_mesh_create(verts, 4, indices, 6);

  spr.x = 0.0f;
  spr.y = 0.0f;
  spr.scale_x = 1.0f;
  spr.scale_y = 1.0f;
  spr.rotation = 0.0f;

  return spr;
}

void lin_sprite_draw(lin_sprite sprite) {
  lr_shader *shader = &_CUR_SHADER;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sprite.tex.id);

  mat4 model;
  glm_mat4_identity(model);

  // Translation
  vec3 pos = {sprite.x, sprite.y, 0.0f};
  glm_translate(model, pos);

  // Rotation (around center)
  float half_w = (sprite.tex.width * sprite.scale_x) / 2.0f;
  float half_h = (sprite.tex.height * sprite.scale_y) / 2.0f;

  vec3 center = {half_w, half_h, 0.0f};
  glm_translate(model, center);
  glm_rotate(model, sprite.rotation, (vec3){0.0f, 0.0f, 1.0f});
  vec3 neg_center = {-half_w, -half_h, 0.0f};
  glm_translate(model, neg_center);

  // Scaling (native texture size * user scale)
  vec3 scale = {sprite.tex.width * sprite.scale_x,
                sprite.tex.height * sprite.scale_y, 1.0f};
  glm_scale(model, scale);

  int model_loc = glGetUniformLocation(shader->id, "u_model");
  if (model_loc != -1) {
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float *)model);
  }

  lr_mesh_draw(sprite.mesh);
}

void lin_sprite_destroy(lin_sprite sprite) {
  lr_mesh_destroy(sprite.mesh);
  glDeleteTextures(1, &sprite.tex.id);
}
