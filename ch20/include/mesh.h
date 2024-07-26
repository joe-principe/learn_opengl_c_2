#ifndef MESH_H
#define MESH_H

#include "../include/shader.h"

#include <cglm/cglm.h>

typedef struct vertex vertex;
typedef struct texture texture;
typedef struct mesh mesh;

struct vertex
{
    vec3 position;
    vec3 normal;
    vec3 tex_coords;
};

struct texture
{
    unsigned int id;
    const char *type;
};

struct mesh
{
    vertex *vertices;
    unsigned int *indices;
    texture *textures;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

/**
 * @brief Creates a new mesh object
 *
 * @param[in] vertices The mesh's vertices
 * @param[in] indices The indices of each vertex
 * @param[in] textures The mesh's textures
 *
 * @note Each of the parameters should be stb_ds dynamic arrays. That said,
 * regular arrays or even pointers to a single object should still work out
 * alright
 * 
 * @return A pointer to the newly created mesh object
 */
mesh *create_mesh(vertex *vertices, unsigned int *indices, texture *textures);

/**
 * @brief Draws the mesh
 *
 * @param[in] mesh The mesh to draw
 * @param[in] shader The shader this mesh uses
 */
void draw_mesh(mesh *mesh, shader *shader);

/**
 * @brief Initializes the buffer objects (vao, vbo, ebo)
 *
 * @param[in] mesh The mesh to configure
 */
void setup_mesh(mesh *mesh);

#endif
/* EOF */
