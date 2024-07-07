#include <stdio.h>
#include <stdlib.h>

#include "../include/shader.h"

void
create_shader(shader *sh, const char *vertex_path, const char *fragment_path)
{
    FILE *vs_fp;
    FILE *fs_fp;

    char *vs_buf;
    char *fs_buf;
    long length;

    unsigned int vs;
    unsigned int fs;

    int is_vertex_compiled;
    int is_fragment_compiled;
    int is_sp_linked;

    int max_length;

    char *vertex_info_log;
    char *fragment_info_log;
    char *shader_program_info_log;

    /* === Vertex Shader === */
    if ((vs_fp = fopen(vertex_path, "rb")) == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", vertex_path);
        exit(EXIT_FAILURE);
    }

    fseek(vs_fp, 0, SEEK_END);
    length = ftell(vs_fp);

    vs_buf = calloc(length + 1, sizeof(*vs_buf));

    if (vs_buf == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for vertex shader "
                "string\n");
        exit(EXIT_FAILURE);
    }

    fseek(vs_fp, 0, SEEK_SET);
    fread(vs_buf, length, 1, vs_fp);
    fclose(vs_fp);

    vs_buf[length] = 0;

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, (const char **)&vs_buf, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &is_vertex_compiled);
    if (!is_vertex_compiled) {
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &max_length);

        vertex_info_log = calloc(max_length, sizeof(*vertex_info_log));

        glGetShaderInfoLog(vs, max_length, NULL, vertex_info_log);

        fprintf(stderr, "Error: Vertex Shader Compilation Failed\n");
        fprintf(stderr, "%s", vertex_info_log);

        free(vertex_info_log);
        vertex_info_log = NULL;
    }

    free(vs_buf);
    vs_buf = NULL;

    /* === Fragment Shader === */
    if ((fs_fp = fopen(fragment_path, "rb")) == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", fragment_path);
        exit(EXIT_FAILURE);
    }

    fseek(fs_fp, 0, SEEK_END);
    length = ftell(fs_fp);

    fs_buf = calloc(length + 1, sizeof(*fs_buf));

    if (fs_buf == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for fragment shader "
                "string\n");
        exit(EXIT_FAILURE);
    }

    fseek(fs_fp, 0, SEEK_SET);
    fread(fs_buf, length, 1, fs_fp);
    fclose(fs_fp);

    fs_buf[length] = 0;

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, (const char **)&fs_buf, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &is_fragment_compiled);
    if (!is_fragment_compiled) {
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &max_length);

        fragment_info_log = calloc(max_length, sizeof(*fragment_info_log));

        glGetShaderInfoLog(fs, max_length, NULL, fragment_info_log);

        fprintf(stderr, "Error: Fragment Shader Compilation Failed\n");
        fprintf(stderr, "%s", fragment_info_log);

        free(fragment_info_log);
        fragment_info_log = NULL;
    }

    free(fs_buf);
    fs_buf = NULL;

    /* === Shader Program === */
    sh->ID = glCreateProgram();
    glAttachShader(sh->ID, vs);
    glAttachShader(sh->ID, fs);
    glLinkProgram(sh->ID);

    glGetProgramiv(sh->ID, GL_LINK_STATUS, &is_sp_linked);
    if (!is_sp_linked) {
        glGetProgramiv(sh->ID, GL_INFO_LOG_LENGTH, &max_length);

        shader_program_info_log = calloc(max_length,
                                         sizeof(*shader_program_info_log));

        glGetProgramInfoLog(sh->ID, max_length, NULL, shader_program_info_log);

        fprintf(stderr, "Error: Shader Program Linking Failed\n");
        fprintf(stderr, "%s", shader_program_info_log);

        free(shader_program_info_log);
        shader_program_info_log = NULL;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void
use_shader(shader *sh)
{
    glUseProgram(sh->ID);
}

void
set_shader_bool(shader *sh, const char *name, bool value)
{
    glUniform1i(glGetUniformLocation(sh->ID, name), (int)value);
}

void
set_shader_int(shader *sh, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(sh->ID, name), value);
}

void
set_shader_float(shader *sh, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(sh->ID, name), value);
}
/* EOF */
