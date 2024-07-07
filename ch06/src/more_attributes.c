#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    unsigned int vertex_shader;
    unsigned int fragment_shader;
    unsigned int shader_program;

    GLFWwindow *window = NULL;

    /* int num_attributes; */

    int is_compiled_vs;
    int is_compiled_fs;
    int is_linked_sp;

    int max_length;
    char *vertex_info_log;
    char *fragment_info_log;
    char *shader_program_info_log;

    float vertices[] = {
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    const char *vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos, 1.0);\n"
        " ourColor = aColor;\n"
        "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(ourColor, 1.0);\n"
        "}\0";

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

    /* === Vertex Shader === */

    /*
     * The vertex shader is the GPU program that transforms 3D world coordinates
     * into 3D projected coordinates. It can also apply transformations upon the
     * vertices it receives
     */

    /* Like the VBO, we generate an ID for the vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    /* Then, we attach the shader source code and compile it */
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    /* We check if the vertex shader compiled correctly */
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled_vs);
    if (!is_compiled_vs) {
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

        vertex_info_log = calloc(max_length, sizeof(*vertex_info_log));

        glGetShaderInfoLog(vertex_shader, max_length, NULL, vertex_info_log);

        fprintf(stderr, "Error: Vertex Shader Compilation Failed.\n");
        fprintf(stderr, "%s", vertex_info_log);

        free(vertex_info_log);
        vertex_info_log = NULL;
    }

    /* === Fragment Shader === */

    /*
     * The fragment shader is the GPU program that calculates the output colors
     * of the pixels. It's created and compiled the same way as the vertex
     * shader, so all of the following should look familiar.
     */

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled_fs);
    if (!is_compiled_fs) {
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

        fragment_info_log = calloc(max_length, sizeof(*fragment_info_log));

        glGetShaderInfoLog(fragment_shader, max_length, NULL,
                           fragment_info_log);

        fprintf(stderr, "Error: Fragment Shader Compilation Failed.\n");
        fprintf(stderr, "%s", fragment_info_log);

        free(fragment_info_log);
        fragment_info_log = NULL;
    }

    /* === Shader Program === */

    /* 
     * A shader program is an OpenGL object that links multiple shaders together
     * so it itself can be used when issuing render calls rather than the
     * individual shaders.
     */

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &is_linked_sp);
    if (!is_linked_sp) {
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_length);

        shader_program_info_log = calloc(max_length,
                                         sizeof(*shader_program_info_log));

        glGetProgramInfoLog(shader_program, max_length, NULL,
                            shader_program_info_log);

        fprintf(stderr, "Error: Shader Program Linking Failed.\n");
        fprintf(stderr, "%s", shader_program_info_log);

        free(shader_program_info_log);
        shader_program_info_log = NULL;
    }

    glUseProgram(shader_program);

    /* After linking the shaders to the shader program, they can be deleted */
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);

        /* When drawing by indices rather than by vertices, use the EBO */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);

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
