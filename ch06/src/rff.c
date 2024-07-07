#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>

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

int
main(void)
{
    unsigned int VBO;
    unsigned int VAO;

    shader sh;

    GLFWwindow *window = NULL;

    /* int num_attributes; */

    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    /* Instantiate the GLFW window */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Hello triangle", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Error: Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Error: Failed to initialize GLAD\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* 
     * glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num_attributes);
     * printf("Max number of vertex attributes supported: %d\n", num_attributes);
     */

    /* === Vertex Array Object === */

    /*
     * VAOs store pointers to VBOs, allowing us to bind a different VAO whenever
     * we want to switch between vertex data and attribute configurations,
     * rather than having to rebind everything related to the VBO and its
     * attributes.
     */
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* === Vertex Buffer Object === */

    /* 
     * A VBO is an array in the GPU's memory that can store lots of vertices. It
     * allows us to send big chunks of data to the GPU all at once rather than
     * each vertex individually.
     */

    /* We generate the ID for and bind to the new buffer here */
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* We then copy the vertex data to the VBO */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* === Vertex Attributes === */

    /*
     * 0 is the attribute we want to configure (the location which was specified
     * in the vertex shader, in this case)
     *
     * 3 is the size of the attribute
     *
     * GL_FLOAT is the type of the attribute
     *
     * GL_FALSE says we don't want to normalize the data
     *
     * 3 * sizeof(float) is the stride (space) between attributes
     *
     * (void *) 0 is the offset where the data begins from the start of the
     * buffer
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    create_shader(&sh,
              "/home/joe/Programming/c/learn_opengl/ch06/shaders/shader.vs",
              "/home/joe/Programming/c/learn_opengl/ch06/shaders/shader.fs");

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        use_shader(&sh);
        glBindVertexArray(VAO);

        /* When drawing by indices rather than by vertices, use the EBO */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
/* EOF */
