#version 330 core
layout (location = 0) in vec3 aPos; // Position has attribute position 0

uniform vec2 offset; // Horizontal and vertical offset uniform

out vec3 ourPosition; // Output a position to the fragment shader

void main()
{
        gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0);
        ourPosition = aPos;
}
