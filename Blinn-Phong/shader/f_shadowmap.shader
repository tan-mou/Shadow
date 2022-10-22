#version 330 core
out vec4 FragColor;
in vec4 frag_pos;
float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth ; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depth = LinearizeDepth(frag_pos.z/frag_pos.w) / far; // 为了演示除以 far
    FragColor = vec4(vec3(depth), 1.0);
}