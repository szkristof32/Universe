#version 450 core

layout (location = 0) in vec3 pass_position;
layout (location = 1) in vec3 pass_cameraPosition;

layout (location = 0) out vec4 out_colour;

const float maxGridDistance = 100.0;
const float gridSmoothing = 10.0;

void main()
{
	vec3 cameraPosition = pass_cameraPosition;
	float opacity = smoothstep(maxGridDistance, maxGridDistance + gridSmoothing, length(pass_position - cameraPosition));
	out_colour = vec4(0.3, 0.3, 0.3, 0.7 * (1.0 - opacity));
}
