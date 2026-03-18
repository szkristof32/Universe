#version 450 core

layout (location = 0) in vec3 in_position;

layout (std140, binding = 0) uniform Camera
{
	mat4 Projection;
	mat4 View;
} u_camera;

void main()
{
	gl_Position = u_camera.Projection * u_camera.View * vec4(in_position, 1.0);
}
