#version 330 core
out vec4 FragColor;

in vec2 o_uv;

uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, o_uv);
}