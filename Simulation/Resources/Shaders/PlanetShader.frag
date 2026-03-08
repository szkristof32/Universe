#version 460 core

layout (location = 0) in Output
{
	vec3 Normal;
	vec4 Colour;
} pass_input;

layout (location = 0) out vec4 out_colour;

void main()
{
	out_colour = pass_input.Colour;
}
