//
// linear.h - v0.0.1
// ---------------------------------------------------------
// A lightweight C99 wrapper for CGLM, GLAD, & GLFW.
// Created specifically as a hobby project.
// It shows my journey of learning visual programming as a mediocre C
// programmer.
//
// ---------------------------------------------------------------
//
// Copyright (c) 2026 Rei Taylor
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// ---------------------------------------------------------------
//
// for any bugs found, you can always file an issue
// i'll be more than happy to fix :)
//

#ifndef LR_LIN
#define LR_LIN "0.0.1"

#include "file_util.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "window.h"

#include <cglm/cglm.h>

#include <stdbool.h>
#include <stdio.h>

// we use the lin poorman's prefix here
// and keep lr (linear render) for the raw stuff
lr_window *lin_window_init(int width, int height, const char *caption);
bool lin_window_close();
void lin_draw_begin();
void lin_draw_end();
void lin_use_shader(lr_shader shader);

typedef struct {
  lr_texture tex;
  lr_mesh mesh;
  float x, y;
  float scale_x, scale_y;
  float rotation;
} lin_sprite;

lin_sprite lin_sprite_create(const char *image_path);
void lin_sprite_draw(lin_sprite sprite);
void lin_sprite_destroy(lin_sprite sprite);

#endif