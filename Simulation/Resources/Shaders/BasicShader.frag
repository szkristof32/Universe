#version 460 core

layout (location = 0) in Output
{
	vec3 Normal;
} pass_input;

layout (location = 0) out vec4 out_colour;

layout (std140, binding = 1) uniform Properties
{
	vec4 Colour;
} u_properties;

void main()
{
	out_colour = u_properties.Colour;
}
