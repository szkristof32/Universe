#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) out Output
{
	vec3 Normal;
	vec4 Colour;
} pass_output;

layout (std140, binding = 0) uniform Camera
{
	mat4 Projection;
	mat4 View;
} u_camera;

layout (std140, binding = 1) uniform Properties
{
	mat4 Transformation;
	vec4 Colour;
} u_properties;

void main()
{
	pass_output.Normal = (u_properties.Transformation * vec4(in_normal, 0.0)).xyz;
	pass_output.Colour = u_properties.Colour;

	gl_Position = u_camera.Projection * u_camera.View * u_properties.Transformation * vec4(in_position, 1.0);
}
