#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>
#include <glad/glad.h>

typedef struct shader shader;

struct shader
{
    unsigned int ID;
};

/**
 * @brief Reads and compiles vertex and fragment shaders, then links them into a
 * shader program
 *
 * @param[in, out] sh The shader struct
 * @param[in] vertex_path The path to the vertex shader
 * @param[in] fragment_path The path to the fragment shader
 */
void create_shader(shader *sh,
                   const char *vertex_path,
                   const char *fragment_path);

/**
 * @brief Uses the shader program
 *
 * @param[in] sh The shader struct
 */
void use_shader(shader *sh);

/**
 * @brief Sets the value of a bool within the shader program
 *
 * @param[in] sh The shader struct
 * @param[in] name The name of the value to set
 * @param[in] value The new value
 */
void set_shader_bool(shader *sh, const char *name, bool value);

/**
 * @brief Sets the value of an int within the shader program
 *
 * @param[in] sh The shader struct
 * @param[in] name The name of the value to set
 * @param[in] value The new value
 */
void set_shader_int(shader *sh, const char *name, int value);

/**
 * @brief Sets the value of a float within the shader program
 *
 * @param[in] sh The shader struct
 * @param[in] name The name of the value to set
 * @param[in] value The new value
 */
void set_shader_float(shader *sh, const char *name, float value);

#endif
/* EOF */
