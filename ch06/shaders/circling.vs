#version 330 core
layout (location = 0) in vec3 aPos; // Position has attribute position 0
layout (location = 1) in vec3 aColor; // Color has attribute position 1

uniform vec2 offset;

out vec3 ourColor; // Output a color to the fragment shader

void main()
{
        gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0);
        ourColor = aColor; // Set ourColor to input color from the vertex data
}
