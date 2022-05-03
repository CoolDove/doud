#version 450 core

layout (location = 0) out vec4 FragColor;

in vec2 v2f_uv;

void main() {
	vec4 col = vec4(v2f_uv, 0, 1);
    FragColor = col;
}
