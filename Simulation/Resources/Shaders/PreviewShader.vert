#version 450 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_colour;

layout (location = 0) out vec4 pass_colour;

layout (std140, binding = 0) uniform Camera
{
	mat4 Projection;
	mat4 View;
} u_camera;

void main()
{
	pass_colour = in_colour;

	gl_Position = u_camera.Projection * u_camera.View * vec4(in_position, 1.0);
}
