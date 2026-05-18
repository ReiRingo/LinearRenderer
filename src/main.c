#include "linear.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  lr_window *ex = lin_window_init(640, 480, "Example Window");

  if (!ex)
    return -1;

  lr_shader shader =
      lr_shader_load("shaders/default.vert", "shaders/default.frag");

  // load the texture via lin_sprite
  lin_sprite nanami = lin_sprite_create("assets/test_image.png");
  nanami.x = 20.0f;
  nanami.y = 20.0f;
  nanami.scale_x = 0.3f;
  nanami.scale_y = 0.3f;

  while (!lr_window_should_close(ex)) {
    lin_draw_begin();

    lin_use_shader(shader);

    lin_sprite_draw(nanami);

    lin_draw_end();
  }

  lin_sprite_destroy(nanami);
  lin_window_close();

  return 0;
}