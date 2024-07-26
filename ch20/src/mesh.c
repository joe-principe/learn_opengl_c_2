#include <stddef.h>

#include "../include/mesh.h"
#include "../include/shader.h"

#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include <glad/glad.h>

mesh *
create_mesh(vertex *vertices, unsigned int *indices, texture *textures)
{
    mesh *m = malloc(sizeof(*m));

    if (m == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for mesh\n");
        exit(EXIT_FAILURE);
    }

    m->vertices = vertices;
    m->indices = indices;
    m->textures = textures;

    setup_mesh(m);

    return m;
}

void
draw_mesh(mesh *mesh, shader *shader)
{
    unsigned int diffuse_num = 1;
    unsigned int specular_num = 1;
    unsigned int i;

    char number[3] = {0};
    const char *name = NULL;

    char sampler_uniform_str[28];

    for (i = 0; i < arrlen(mesh->textures); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        name = mesh->textures[i].type;

        if (strcmp(name, "texture_diffuse") == 0) {
            snprintf(number, 2, "%d", diffuse_num);
            diffuse_num++;
        }
        else if (strcmp(name, "texture_specular") == 0) {
            snprintf(number, 2, "%d", specular_num);
            specular_num++;
        }

        snprintf(sampler_uniform_str, 27, "material.%s%s", name, number);
        set_shader_1f(shader->ID, sampler_uniform_str, i);
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, arrlen(mesh->indices), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void
setup_mesh(mesh *mesh)
{
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);

    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

    glBufferData(GL_ARRAY_BUFFER, arrlen(mesh->vertices) * sizeof(vertex),
                 &mesh->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 arrlen(mesh->indices) * sizeof(unsigned int),
                 &mesh->indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned int),
                          offsetof(struct vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(texture),
                          offsetof(struct vertex, tex_coords));

    glBindVertexArray(0);
}

/* EOF */
