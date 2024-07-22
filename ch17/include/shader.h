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
 * @brief Sets the value of an int uniform within the shader program
 * @note Calls glGetUniform1i
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] value The new value
 */
void set_shader_1i(unsigned int id, const char *name, int v0);

/**
 * @brief Sets the value of an int uniform within the shader program
 * @note Calls glGetUniform2i
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 */
void set_shader_2i(unsigned int id, const char *name, int v0, int v1);

/**
 * @brief Sets the value of an int uniform within the shader program
 * @note Calls glGetUniform3i
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 */
void set_shader_3i(unsigned int id, const char *name, int v0, int v1, int v2);

/**
 * @brief Sets the value of an int uniform within the shader program
 * @note Calls glGetUniform4i
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 * @param[in] v3 The fourth parameter's value
 */
void set_shader_4i(unsigned int id, const char *name, int v0, int v1, int v2,
                   int v3);

/**
 * @brief Sets the value of a float within the shader program
 * @note Calls glGetUniform1f
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] value The new value
 */
void set_shader_1f(unsigned int id, const char *name, float v0);

/**
 * @brief Sets the value of a float within the shader program
 * @note Calls glGetUniform2f
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 */
void set_shader_2f(unsigned int id, const char *name, float v0, float v1);

/**
 * @brief Sets the value of a float within the shader program
 * @note Calls glGetUniform3f
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 */
void set_shader_3f(unsigned int id, const char *name, float v0, float v1,
                   float v2);

/**
 * @brief Sets the value of a float uniform within the shader program
 * @note Calls glGetUniform4f
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 * @param[in] v3 The fourth parameter's value
 */
void set_shader_4f(unsigned int id, const char *name, float v0, float v1,
                   float v2, float v3);

/**
 * @brief Sets the value of an unsigned int uniform within the shader program
 * @note Calls glGetUniform1ui
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The new value
 */
void set_shader_1ui(unsigned int id, const char *name, unsigned int v0);

/**
 * @brief Sets the value of an unsigned int uniform within the shader program
 * @note Calls glGetUniform2ui
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 */
void set_shader_2ui(unsigned int id, const char *name, unsigned int v0,
                    unsigned int v1);

/**
 * @brief Sets the value of an unsigned int uniform within the shader program
 * @note Calls glGetUniform3ui
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 */
void set_shader_3ui(unsigned int id, const char *name, unsigned int v0,
                    unsigned int v1, unsigned int v2);

/**
 * @brief Sets the value of an unsigned int uniform within the shader program
 * @note Calls glGetUniform4ui
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] v0 The first parameter's value
 * @param[in] v1 The second parameter's value
 * @param[in] v2 The third parameter's value
 * @param[in] v3 The fourth parameter's value
 */
void set_shader_4ui(unsigned int id, const char *name, unsigned int v0,
                    unsigned int v1, unsigned int v2, unsigned int v3);

/**
 * @brief Sets the value of a float array uniform within the shader program
 * @note Calls glGetUniform1fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The float array
 */
void set_shader_1fv(unsigned int id, const char *name, GLsizei count,
                    const float *value);

/**
 * @brief Sets the value of a float array uniform within the shader program
 * @note Calls glGetUniform2fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The float array
 */
void set_shader_2fv(unsigned int id, const char *name, GLsizei count,
                    const float *value);

/**
 * @brief Sets the value of a float array uniform within the shader program
 * @note Calls glGetUniform3fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The float array
 */
void set_shader_3fv(unsigned int id, const char *name, GLsizei count,
                    const float *value);

/**
 * @brief Sets the value of a float array uniform within the shader program
 * @note Calls glGetUniform4fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The float array
 */
void set_shader_4fv(unsigned int id, const char *name, GLsizei count,
                    const float *value);

/**
 * @brief Sets the value of an integer array uniform within the shader program
 * @note Calls glGetUniform1iv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The integer array
 */
void set_shader_1iv(unsigned int id, const char *name, GLsizei count,
                    const GLint *value);

/**
 * @brief Sets the value of an integer array uniform within the shader program
 * @note Calls glGetUniform2iv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The integer array
 */
void set_shader_2iv(unsigned int id, const char *name, GLsizei count,
                    const GLint *value);

/**
 * @brief Sets the value of an integer array uniform within the shader program
 * @note Calls glGetUniform3iv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The integer array
 */
void set_shader_3iv(unsigned int id, const char *name, GLsizei count,
                    const GLint *value);

/**
 * @brief Sets the value of an integer array uniform within the shader program
 * @note Calls glGetUniform4iv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The integer array
 */
void set_shader_4iv(unsigned int id, const char *name, GLsizei count,
                    const GLint *value);

/**
 * @brief Sets the value of an unsigned integer array uniform within the shader
 * program
 * @note Calls glGetUniform1uiv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The unsigned integer array
 */
void set_shader_1uiv(unsigned int id, const char *name, GLsizei count,
                    const GLuint *value);

/**
 * @brief Sets the value of an unsigned integer array uniform within the shader
 * program
 * @note Calls glGetUniform2uiv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The unsigned integer array
 */
void set_shader_2uiv(unsigned int id, const char *name, GLsizei count,
                    const GLuint *value);

/**
 * @brief Sets the value of an unsigned integer array uniform within the shader
 * program
 * @note Calls glGetUniform3uiv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The unsigned integer array
 */
void set_shader_3uiv(unsigned int id, const char *name, GLsizei count,
                    const GLuint *value);

/**
 * @brief Sets the value of an unsigned integer array uniform within the shader
 * program
 * @note Calls glGetUniform4uiv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of elements to be modified
 * @param[in] value The unsigned integer array
 */
void set_shader_4uiv(unsigned int id, const char *name, GLsizei count,
                    const GLuint *value);

/**
 * @brief Sets the value of a float matrix uniform within the shader program
 * @note Calls glGetUniformMatrix4fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of matrices to be modified
 * @param[in] transpose If the matrix should be transposed
 * @param[in] value The float matrix
 */
void set_shader_mat4fv(unsigned int id, const char *name, GLsizei count,
                       GLboolean transpose, const float *value);

/**
 * @brief Sets the value of a float matrix uniform within the shader program
 * @note Calls glGetUniformMatrix3fv
 *
 * @param[in] id The shader's ID
 * @param[in] name The name of the uniform value to be modified
 * @param[in] count The number of matrices to be modified
 * @param[in] transpose If the matrix should be transposed
 * @param[in] value The float matrix
 */
void set_shader_mat3fv(unsigned int id, const char *name, GLsizei count,
                       GLboolean transpose, const float *value);
#endif
/* EOF */
