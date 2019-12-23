#version 330 core

in vec3 ourCol;
in vec2 ourTex;

uniform sampler2D aTex0;
uniform sampler2D aTex1;

out vec4 fragColor;

void main()
{
    fragColor = mix(texture(aTex0, ourTex), texture(aTex1, ourTex), 0.2) * vec4(ourCol, 1.0);
}