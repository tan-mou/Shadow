#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 anormal;
layout(location = 2) in vec2 uv;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
out vec4 frag_pos;
void main() {


	gl_Position = u_projection * u_view * u_model * vec4(position, 1);
    frag_pos = u_projection * u_view * u_model * vec4(position, 1);
	
}