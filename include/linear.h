//
// linear.h - v0.0.1
// ---------------------------------------------------------
// A lightweight C99 wrapper for CGLM, GLAD, & GLFW.
// Created specifically as a hobby project.
// It shows my journey of learning visual programming as a mediocre C programmer.
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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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

#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "file_util.h"

#include <cglm/cglm.h>

#include <stdio.h>
#include <stdbool.h>

// we use the lin poorman's prefix here
// and keep lr (linear render) for the raw stuff
lr_window* lin_window_init(int width, int height, const char* caption);
bool       lin_window_close();
#endif