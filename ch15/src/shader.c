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
        fprintf(stderr, "Error when trying to parse vertex shader: %s\n",
                vertex_path);
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

        fprintf(stderr, "Error: Vertex Shader Compilation Failed: %s\n",
                vertex_path);
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
        fprintf(stderr, "Error when trying to parse fragment shader: %s\n",
                fragment_path);
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

        fprintf(stderr, "Error: Fragment Shader Compilation Failed: %s\n",
                fragment_path);
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
set_shader_1i(unsigned int id, const char *name, int v0)
{
    glUniform1i(glGetUniformLocation(id, name), v0);
}

void
set_shader_2i(unsigned int id, const char *name, int v0, int v1)
{
    glUniform2i(glGetUniformLocation(id, name), v0, v1);
}

void
set_shader_3i(unsigned int id, const char *name, int v0, int v1, int v2)
{
    glUniform3i(glGetUniformLocation(id, name), v0, v1, v2);
}

void
set_shader_4i(unsigned int id, const char *name, int v0, int v1, int v2, int v3)
{
    glUniform4i(glGetUniformLocation(id, name), v0, v1, v2, v3);
}

void
set_shader_1f(unsigned int id, const char *name, float v0)
{
    glUniform1f(glGetUniformLocation(id, name), v0);
}

void
set_shader_2f(unsigned int id, const char *name, float v0, float v1)
{
    glUniform2f(glGetUniformLocation(id, name), v0, v1);
}

void
set_shader_3f(unsigned int id, const char *name, float v0, float v1, float v2)
{
    glUniform3f(glGetUniformLocation(id, name), v0, v1, v2);
}

void
set_shader_4f(unsigned int id, const char *name, float v0, float v1, float v2,
              float v3)
{
    glUniform4f(glGetUniformLocation(id, name), v0, v1, v2, v3);
}

void 
set_shader_1ui(unsigned int id, const char *name, unsigned int v0)
{
    glUniform1ui(glGetUniformLocation(id, name), v0);
}

void 
set_shader_2ui(unsigned int id, const char *name, unsigned int v0,
               unsigned int v1)
{
    glUniform2ui(glGetUniformLocation(id, name), v0, v1);
}

void 
set_shader_3ui(unsigned int id, const char *name, unsigned int v0,
               unsigned int v1, unsigned int v2)
{
    glUniform3ui(glGetUniformLocation(id, name), v0, v1, v2);
}

void 
set_shader_4ui(unsigned int id, const char *name, unsigned int v0,
               unsigned int v1, unsigned int v2, unsigned int v3)
{
    glUniform4ui(glGetUniformLocation(id, name), v0, v1, v2, v3);
}

void 
set_shader_1fv(unsigned int id, const char *name, GLsizei count,
               const float *value)
{
    glUniform1fv(glGetUniformLocation(id, name), count, value);
}

void 
set_shader_2fv(unsigned int id, const char *name, GLsizei count,
               const float *value)
{
    glUniform2fv(glGetUniformLocation(id, name), count, value);
}

void 
set_shader_3fv(unsigned int id, const char *name, GLsizei count,
               const float *value)
{
    glUniform3fv(glGetUniformLocation(id, name), count, value);
}

void 
set_shader_4fv(unsigned int id, const char *name, GLsizei count,
               const float *value)
{
    glUniform4fv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_1iv(unsigned int id, const char *name, GLsizei count,
               const GLint *value)
{
    glUniform1iv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_2iv(unsigned int id, const char *name, GLsizei count,
               const GLint *value)
{
    glUniform2iv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_3iv(unsigned int id, const char *name, GLsizei count,
               const GLint *value)
{
    glUniform3iv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_4iv(unsigned int id, const char *name, GLsizei count,
               const GLint *value)
{
    glUniform4iv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_1uiv(unsigned int id, const char *name, GLsizei count,
                const GLuint *value)
{
    glUniform1uiv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_2uiv(unsigned int id, const char *name, GLsizei count,
                const GLuint *value)
{
    glUniform2uiv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_3uiv(unsigned int id, const char *name, GLsizei count,
                const GLuint *value)
{
    glUniform3uiv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_4uiv(unsigned int id, const char *name, GLsizei count,
                const GLuint *value)
{
    glUniform4uiv(glGetUniformLocation(id, name), count, value);
}

void
set_shader_mat4fv(unsigned int id, const char *name, GLsizei count,
                  GLboolean transpose, const float *value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), count, transpose, value);
}
/* EOF */
