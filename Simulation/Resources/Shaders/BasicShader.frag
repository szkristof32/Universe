#version 460 core

layout (location = 0) out vec4 out_colour;

layout (std140, binding = 1) uniform Properties
{
	vec4 Colour;
} u_properties;

void main()
{
	out_colour = u_properties.Colour;
}
