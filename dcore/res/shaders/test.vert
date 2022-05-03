#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 v2f_uv;

void main() {
	gl_Position = vec4(position.xy, 0.0, 1.0);
	v2f_uv = uv;
}
