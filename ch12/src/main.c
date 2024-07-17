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
    vec3 light_pos = {1.2f, 1.0f, 2.0f};
    vec3 light_color = GLM_VEC3_ONE_INIT;

    vec3 toy_color = {1.0f, 0.5f, 0.31f};

    shader sh;
    shader light_shader;

    const char *vert_shader_path = "shaders/shader.vs";
    const char *frag_shader_path = "shaders/shader.fs";

    const char *light_frag_shader_path = "shaders/light_shader.fs";

    GLFWwindow *window = NULL;

    CGLM_ALIGN_MAT mat4 model = GLM_MAT4_IDENTITY_INIT;
    CGLM_ALIGN_MAT mat4 view = GLM_MAT4_IDENTITY_INIT;
    CGLM_ALIGN_MAT mat4 projection = GLM_MAT4_IDENTITY_INIT;

    vec3 temp = GLM_VEC3_ZERO_INIT;

    float current_frame;

    /* 
     * NOTE: All faces are from the camera's perspective looking head-on (eg,
     * front is directly in front of the camera. Right is camera's right)
     */
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, /* 0 - Front bottom left */
        -0.5f,  0.5f, -0.5f, /* 1 - Front top left */
         0.5f,  0.5f, -0.5f, /* 2 - Front top right */
         0.5f, -0.5f, -0.5f, /* 3 - Front bottom right */
        -0.5f, -0.5f,  0.5f, /* 4 - Back bottom left */
        -0.5f,  0.5f,  0.5f, /* 5 - Back top left */
         0.5f,  0.5f,  0.5f, /* 6 - Back top right */
         0.5f, -0.5f,  0.5f, /* 7 - Back bottom right */
    };

    unsigned int indices[] = {
        /* Front face */
        0, 1, 2,
        2, 3, 0,

        /* Back face */
        4, 5, 6,
        6, 7, 4,

        /* Right face */
        3, 2, 6,
        6, 7, 3,

        /* Left face */
        4, 5, 1,
        1, 0, 4,

        /* Top face */
        1, 5, 6,
        6, 2, 1,

        /* Bottom face */
        3, 7, 4,
        4, 0, 3
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &light_vao);
    glBindVertexArray(light_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    create_shader(&sh, vert_shader_path, frag_shader_path);
    create_shader(&light_shader, vert_shader_path, light_frag_shader_path);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sh.ID);
        glUniform3fv(glGetUniformLocation(sh.ID, "objectColor"), 1,
                     (float *)toy_color);
        glUniform3fv(glGetUniformLocation(sh.ID, "lightColor"), 1,
                     (float *)light_color);

        glBindVertexArray(vao);

        glm_mat4_identity(model);
        glUniformMatrix4fv(glGetUniformLocation(sh.ID, "model"), 1,
                           GL_FALSE, (float *)model);

        glm_mat4_identity(view);
        glm_vec3_add(camera_pos, camera_front, temp);
        glm_lookat(camera_pos, temp, camera_up, view);
        glUniformMatrix4fv(glGetUniformLocation(sh.ID, "view"), 1, GL_FALSE,
                           (float *)view);

        glm_mat4_identity(projection);
        glm_perspective(glm_rad(fov), 800.0f / 600.0f, 0.1f, 100.0f,
                        projection);
        glUniformMatrix4fv(glGetUniformLocation(sh.ID, "projection"), 1,
                           GL_FALSE, (float *)projection);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glUseProgram(light_shader.ID);
        glBindVertexArray(light_vao);

        glm_mat4_identity(model);
        glm_translate(model, light_pos);
        glm_scale(model, (vec3){0.2f, 0.2f, 0.2f});
        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "model"), 1,
                           GL_FALSE, (float *)model);

        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "view"), 1,
                           GL_FALSE, (float *)view);

        glUniformMatrix4fv(glGetUniformLocation(light_shader.ID, "projection"),
                           1, GL_FALSE, (float *)projection);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(sh.ID);

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
    float camera_speed = 2.5f * delta_time;

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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glm_vec3_add(camera_pos, (vec3){0.0f, -camera_speed, 0.0f}, camera_pos);
    }

    /* Moves the camera up */
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        glm_vec3_add(camera_pos, (vec3){0.0f, camera_speed, 0.0f}, camera_pos);
    }
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
