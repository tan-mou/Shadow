#version 330 core
out vec4 FragColor;





//light attribute
struct PointLight {
	vec3 color;
	vec3 position;
	float p;
	float constant;
	float linear;
	float quadratic;
};
struct SpotLight {
	vec3 color;
	vec3 position;
	vec3 direction;
	

	float cutoff;
	float outer_cutoff;

	float p;
	float constant;
	float linear;
	float quadratic;
};
uniform PointLight u_pointlight;
uniform SpotLight u_spotlight;

//dir
struct Dir {
	vec3 light_dir;
	vec3 view_dir;
	float ol_distance;
	float oc_distance;
};
//camera attribute
uniform vec3 u_camerapos;


//object attribute
struct Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};
struct Shadow_Inf {
	float depth;
	vec2 uv;
};
in vec3  normal;
in vec3 o_position;
in vec2 o_uv;
in vec4 world_pos;
uniform sampler2D u_texture;
uniform sampler2D u_texture_specular;
uniform sampler2D u_shadowmap;
uniform mat4 shadow_view;
uniform mat4 shadow_projection;

float near = 0.1;
float far = 100.0;
//function
vec4 Point(PointLight light,Material material, vec3 normal, Dir dir);
Dir GetDir(vec3 o_postion, vec3 c_position, vec3 l_position);
Material SetMaterial(vec3 diffuse, vec3 specular, vec3 ambient);
vec4 Spot(SpotLight light, Material material, vec3 normal, Dir dir);
Shadow_Inf  ShadowTrans(vec4 pos, mat4 view, mat4 projection);

void main() {
	//Material
	Material material = SetMaterial(vec3(texture(u_texture, o_uv)), vec3(texture(u_texture_specular, o_uv)), 0.2 * vec3(texture(u_texture, o_uv)));
	//point light
	Dir p_dir = GetDir(o_position, u_camerapos, u_pointlight.position);
	vec4 result1 = Point(u_pointlight,material, normal, p_dir);
	//Shadow map
	Shadow_Inf sh_inf= ShadowTrans(world_pos,shadow_view, shadow_projection);
	float depth = texture(u_shadowmap, sh_inf.uv).y;
	if (sh_inf.uv.x > 1.0f || sh_inf.uv.y > 1.0f|| sh_inf.uv.x < 0.0f || sh_inf.uv.y < 0.0f) {
		FragColor = result1;
	}
	else {
		float bias = max(0.05 * (1.0 - dot(normal, p_dir.light_dir)), 0.005);
		if ( sh_inf.depth-0.002>depth) {
			FragColor = 0.2*texture(u_texture, o_uv);
		}
		else {
			FragColor = result1;
		}
	}
	
	//spot light
	/*Dir s_dir = GetDir(o_position, u_camerapos, u_spotlight.position);
	vec4 result2 = Spot(u_spotlight, material, normal, s_dir);*/

	//reuslt

	/*FragColor = result2+result1;*/
	

}
Material SetMaterial(vec3 diffuse,vec3 specular, vec3 ambient) {
	Material material;
	material.diffuse = diffuse;
	material.specular = specular;
	material.ambient = ambient;
	return material;
}
Dir GetDir(vec3 o_postion, vec3 c_position, vec3 l_position) {
	Dir dir;
	dir.light_dir =normalize(o_position - l_position);
	dir.view_dir = normalize(o_position - c_position);
	dir.ol_distance = length(o_position - l_position);
	dir.oc_distance = length(o_position - c_position);
	return dir;
}


vec4 Spot(SpotLight light, Material material, vec3 normal, Dir dir) {

	//thata compare
	float theta = dot(dir.light_dir,light.direction);
	float I = (theta-light.outer_cutoff)/(light.cutoff-light.outer_cutoff);

	//distance  coeffient
	float d = dir.ol_distance;
	float F = 1 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));


	//diffuse
	float nl = dot(-dir.light_dir, normal);
	vec3 diffuse = material.diffuse * F * light.color * max(0, nl);
	//specular
	vec3 h = normalize(-dir.light_dir + (-dir.view_dir));
	float nh = dot(h, normal);
	vec3 specular = material.specular * F * light.color * max(0, pow(nh, light.p));
	//ambient
	vec3 ambient = material.ambient * light.color;
	vec4 result = vec4(diffuse + ambient + specular, 1.0f);
	if (theta >= light.cutoff) {
		
		return result;
	}
	else if (theta < light.cutoff && theta >= light.outer_cutoff) {

		return I*result;
	}
	else {
		
		return vec4(0);

	}
}

vec4 Point(PointLight light,Material material,vec3 normal,Dir dir){
	//distance  coeffient
	float d = dir.ol_distance;
	float F = 1 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));


	//diffuse
	float nl = dot(-dir.light_dir, normal);
	vec3 diffuse = material.diffuse*F*light.color * max(0,nl);
	//specular
	vec3 h = normalize(-dir.light_dir + (-dir.view_dir));
	float nh = dot(h, normal);
	vec3 specular =  F*light.color * max(0, pow(nh, light.p));
	//ambient
	vec3 ambient = material.ambient * light.color;
	vec4 result=vec4(diffuse+ambient+specular,1.0f);
	return result;
}

Shadow_Inf  ShadowTrans(vec4 pos, mat4 view, mat4 projection) {
	vec4 shadow_pos = projection * view * pos;
	float shadow_z = shadow_pos.z / shadow_pos.w;
	float depth = (2.0 * near * far) / (far + near - shadow_z * (far - near))/far;
	float u = (shadow_pos.x / shadow_pos.w + 1) / 2;
	float v = (shadow_pos.y / shadow_pos.w + 1) / 2;
	vec2 shadow_uv = vec2(u, v);
	Shadow_Inf inf;
	inf.uv = shadow_uv;
	inf.depth = depth;
	return inf;

}
