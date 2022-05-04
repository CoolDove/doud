#version 450 core

layout (location = 0) out vec4 FragColor;

in vec2 v2f_uv;

uniform sampler2D noise;

void main() {
	vec4 col = texture(noise, v2f_uv * vec2(1, -1));
    FragColor = col;
}
