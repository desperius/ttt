#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

out vec3 ourCol;
out vec2 ourTex;

void main()
{
    gl_Position = vec4(pos, 1.0);
    ourCol = col;
    ourTex = tex;
}