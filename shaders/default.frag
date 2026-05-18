#version 330 core

#define frag_colour frag_color

out vec4 frag_color;

in vec2 v_tex_coord;
uniform sampler2D u_texture;

void main() {
    frag_colour = texture(u_texture, v_tex_coord);
}