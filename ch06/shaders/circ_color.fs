#version 330 core
out vec4 FragColor;

uniform vec2 offset; // Horizontal and vertical offset uniform
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0);
}
