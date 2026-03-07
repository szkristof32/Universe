#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) out Output
{
	vec3 Normal;
} pass_output;

layout (std140, binding = 0) uniform Matrices
{
	mat4 ProjectionView;
	mat4 Transformation;
} u_matrices;

void main()
{
	pass_output.Normal = (u_matrices.Transformation * vec4(in_normal, 0.0)).xyz;

	gl_Position = u_matrices.ProjectionView * u_matrices.Transformation * vec4(in_position, 1.0);
}
