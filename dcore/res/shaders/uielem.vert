#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 v2f_uv;

uniform float elem_width;
uniform float elem_height;
uniform float elem_x;
uniform float elem_y;
uniform float viewport_width;
uniform float viewport_height;

void main() {
	vec2 wpos = position.xy * vec2(elem_width, elem_height);
	wpos += vec2(elem_x, elem_y);

	vec2 ndcpos = wpos / vec2(viewport_width, viewport_height);
	ndcpos = 2 * ndcpos - 1;
	ndcpos.y *= -1;

	gl_Position = vec4(ndcpos, 0.0, 1.0);
	v2f_uv = uv;
}
