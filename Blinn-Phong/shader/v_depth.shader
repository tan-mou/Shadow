#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 auv;

out vec3 o_position;
out vec2 o_uv;


void main()
{
    gl_Position = vec4(apos.x, apos.y, 0.0, 1.0);
    o_uv = auv;

}