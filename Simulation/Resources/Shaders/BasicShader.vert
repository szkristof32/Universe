#version 460 core

layout (location = 0) in vec3 in_position;

layout (std140, binding = 0) uniform Matrices
{
	mat4 ProjectionView;
	mat4 Transformation;
} u_matrices;

void main()
{
	gl_Position = u_matrices.ProjectionView * u_matrices.Transformation * vec4(in_position, 1.0);
}
