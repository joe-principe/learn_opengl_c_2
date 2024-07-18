#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include <cglm/cglm.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief The function called whenever the viewport is resized
 *
 * @param[in, out] window The GLFW window that is being resized
 * @param[in] width The new width of the window in pixels
 * @param[in] height The new height of the window in pixels
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/**
 * @brief Responds to any input from the user on the current window
 *
 * @param[in] window The GLFW window whose input is being read
 */
void process_input(GLFWwindow *window);

/**
 * @brief The function called whenever a mouse event is detected
 *
 * @param[in] window The GLFW window
 * @param[in] x_pos The current cursor horizontal position
 * @param[in] y_pos The current cursor vertical position
 */
void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);

/**
 * @brief The function called whenever a mouse event is detected
 *
 * @param[in] window The GLFW window
 * @param[in] x_offset The horizontal scroll amount
 * @param[in] y_offset The vertical scroll amount
 */
void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);

vec3 camera_pos = {0.0f, 0.0f, 3.0f};
vec3 camera_front = {0.0f, 0.0f, -1.0f};
vec3 camera_up = {0.0f, 1.0f, 0.0f};

float delta_time = 0.0f;
float last_frame = 0.0f;

bool first_mouse = true;

float last_x = 400.0f;
float last_y = 300.0f;

float yaw;
float pitch;

float fov = 45.0f;

int
main(void)
{
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

    unsigned int light_vao;
    vec3 light_pos = GLM_VEC3_ONE_INIT;
    vec3 light_color = GLM_VEC3_ONE_INIT;

    vec3 toy_color = {1.0f, 0.5f, 0.31f};

    shader cube_shader;
    shader light_shader;

    const char *cube_vert_shader_path = "shaders/cube_specular.vert";
    const char *cube_frag_shader_path = "shaders/cube_specular.frag";

    const char *light_vert_shader_path = "shaders/light_specular.vert";
    const char *light_frag_shader_path = "shaders/light_specular.frag";

    GLFWwindow *window = NULL;

    CGLM_ALIGN_MAT mat4 model = GLM_MAT4_IDENTITY_INIT;
    CGLM_ALIGN_MAT mat4 view = GLM_MAT4_IDENTITY_INIT;
    CGLM_ALIGN_MAT mat4 projection = GLM_MAT4_IDENTITY_INIT;

    vec3 temp = GLM_VEC3_ZERO_INIT;

    float current_frame;

    float vertices[] = {
        /*         Positions              Normals */
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, /* 00 - Front bottom left */
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, /* 01 - Front bottom right */
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, /* 02 - Front top left */
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, /* 03 - Front top right */

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, /* 04 - Back bottom left */
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, /* 05 - Back bottom right */
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, /* 06 - Back top left */
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, /* 07 - Back top right */

        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, /* 08 - Left bottom left */
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, /* 09 - Left bottom right */
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, /* 10 - Left top left */
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, /* 11 - Left top right */

         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, /* 12 - Right bottom left */
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, /* 13 - Right bottom right */
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, /* 14 - Right top left */
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, /* 15 - Right top right */

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, /* 16 - Top bottom left */
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, /* 17 - Top bottom right */
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, /* 18 - Top top left */
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, /* 19 - Top top right */

         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, /* 20 - Bottom bottom left */
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, /* 21 - Bottom bottom right */
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, /* 22 - Bottom top left */
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f  /* 23 - Bottom top right */
    };

    unsigned int indices[] = {
        /* Front face */
        0, 2, 3,
        3, 1, 0,

        /* Back face */
        4, 6, 7,
        7, 5, 4,

        /* Left face */
        8, 10, 11,
        11, 9, 8,

        /* Right face */
        12, 14, 15,
        15, 13, 12,

        /* Top face */
        16, 18, 19,
        19, 17, 16,

        /* Bottom face */
        20, 22, 23,
        23, 21, 20
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Colors", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Error: Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Error: Failed to initialize GLAD\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &light_vao);
    glBindVertexArray(light_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    create_shader(&cube_shader, cube_vert_shader_path, cube_frag_shader_path);
    create_shader(&light_shader, light_vert_shader_path,
                  light_frag_shader_path);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(cube_shader.ID);
        glUniform3fv(glGetUniformLocation(cube_shader.ID, "objectColor"), 1,
                     (float *)toy_color);
        glUniform3fv(glGetUniformLocation(cube_shader.ID, "lightColor"), 1,
                     (float *)light_color);
        glUniform3fv(glGetUniformLocation(cube_shader.ID, "viewPos"), 1,
                     (float *)camera_pos);

        light_pos[0] = cosf((float)glfwGetTime());
        light_pos[2] = sinf((float)glfwGetTime());

        glUniform3fv(glGetUniformLocation(cube_shader.ID, "lightPos"), 1,
                     (float *)light_pos);

        glm_mat4_identity(model);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader.ID, "model"), 1,
                           GL_FALSE, (float *)model);

        glm_mat4_identity(view);
        glm_vec3_add(camera_pos, camera_front, temp);
        glm_lookat(camera_pos, temp, camera_up, view);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader.ID, "view"), 1,
                           GL_FALSE, (float *)view);

        glm_mat4_identity(projection);
        glm_perspective(glm_rad(fov), 800.0f / 600.0f, 0.1f, 100.0f,
                        projection);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader.ID, "projection"),
                           1, GL_FALSE, (float *)projection);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glUseProgram(light_shader.ID);

        glm_mat4_identity(model);
        glm_translate(model, light_pos);
        glm_scale(model, (vec3){0.2f, 0.2f, 0.2f});
        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "model"), 1,
                           GL_FALSE, (float *)model);

        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "view"), 1,
                           GL_FALSE, (float *)view);

        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "projection"),
                           1, GL_FALSE, (float *)projection);

        glBindVertexArray(light_vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteVertexArrays(1, &light_vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(cube_shader.ID);
    glDeleteProgram(light_shader.ID);

    glfwTerminate();
    return 0;
}

void 
framebuffer_size_callback(GLFWwindow *window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void
process_input(GLFWwindow *window)
{
    float camera_speed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera_speed = 4.5f * delta_time;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera_speed = 0.5f * delta_time;
    else
        camera_speed = 2.5f * delta_time;

    vec3 temp = GLM_VEC3_ZERO_INIT;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    /* Moves the camera forward from its perspective */
    /* camera_pos += camera_front * camera_speed */
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_muladds(camera_front, camera_speed, camera_pos);

    /* Moves the camera backward from its perspective */
    /* camera_pos += camera_front * -camera_speed */
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_muladds(camera_front, -camera_speed, camera_pos);

    /* Moves the camera left from its perspective */
    /* camera_pos += normalize(camera_front x camera_up) * -camera_speed */
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm_cross(camera_front, camera_up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, -camera_speed, camera_pos);
    }

    /* Moves the camera right from its perspective */
    /* camera_pos += normalize(camera_front x camera_up) * camera_speed */
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm_cross(camera_front, camera_up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, camera_speed, camera_pos);
    }

    /* Moves the camera down */
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glm_vec3_add(camera_pos, (vec3){0.0f, -camera_speed, 0.0f}, camera_pos);

    /* Moves the camera up */
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glm_vec3_add(camera_pos, (vec3){0.0f, camera_speed, 0.0f}, camera_pos);
}

void
mouse_callback(GLFWwindow *window, double x_pos, double y_pos)
{
    float x_offset;
    float y_offset;

    const float sensitivity = 0.1f;

    vec3 direction = GLM_VEC3_ZERO_INIT;

    /* 
     * This is supposed to prevent the camera from jerking around when the mouse
     * is first used on the window because its coordinates aren't centered on
     * the window. It doesn't work for some reason
     */
    if (first_mouse) {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
    }

    x_offset = x_pos - last_x;
    y_offset = last_y - y_pos;
    last_x = x_pos;
    last_y = y_pos;

    x_offset *= sensitivity;
    y_offset *= sensitivity;

    yaw += x_offset;
    pitch += y_offset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    direction[1] = sin(glm_rad(pitch));
    direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));

    glm_normalize_to(direction, camera_front);
}

void
scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
    fov -= (float)y_offset;

    if (fov < 1.0f)
        fov = 1.0f;

    if (fov > 45.0f)
        fov = 45.0f;
}
/* EOF */
