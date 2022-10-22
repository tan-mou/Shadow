#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 anormal;
layout(location = 2) in vec2 uv;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
out vec3  normal;
out vec3 o_position;
out vec2 o_uv;
out vec4 world_pos;
void main() {


	gl_Position = u_projection * u_view * u_model * vec4(position, 1);
	world_pos = u_model * vec4(position, 1);
	o_position = vec3(u_model * vec4(position, 1));
	normal = transpose(inverse(mat3(u_model))) * anormal;//这里是法线变换矩阵
	o_uv = uv;
}