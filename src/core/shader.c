#include "window.h"
#include "shader.h"
#include "file_util.h"

static unsigned int lr_compile_shader(unsigned int type, const char* source) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // error checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("Failed to compile %s shader!\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int lr_create_shd_program(const char* vertexSource, const char* fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vs = lr_compile_shader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = lr_compile_shader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        printf("Failed to link program!\n%s\n", message);
    }

    glValidateProgram(program);

    // once linked into the program, we can delete the individual shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

lr_shader_t lr_shader_load(const char* vert_path, const char* frag_path) {
    char* v_src = lr_file_read(vert_path);
    char* f_src = lr_file_read(frag_path);
    
    lr_shader_t shader;
    shader.id = lr_create_shd_program(v_src, f_src);
    
    free(v_src);
    free(f_src);
    return shader;
}

void lr_shader_use(lr_shader_t shd) { glUseProgram(shd.id); }