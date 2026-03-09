#version 460 core

layout (location = 0) in Output
{
	vec3 Normal;
	vec4 Colour;
} pass_input;

layout (location = 0) out vec4 out_colour;

const vec3 s_lightSource = vec3(10.0, 20.0, 8.0);

void main()
{
	vec3 toLight = normalize(s_lightSource);
	vec3 normal = normalize(pass_input.Normal);
	float NdotL = max(dot(normal, toLight), 0.1);

	out_colour = pass_input.Colour * NdotL;
}
