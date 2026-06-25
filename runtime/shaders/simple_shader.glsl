#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
// layout (location = 1) in vec3 a_Color;
// layout (location = 2) in vec3 a_Normal;
// layout (location = 3) in vec3 a_UV;

void main()
{
    gl_Position = vec4(a_Position, 1.0f);
}

#type fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}