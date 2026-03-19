#version 450 core

layout (location = 0) out vec3 pass_position;
layout (location = 1) out vec3 pass_cameraPosition;

layout (std140, binding = 0) uniform Camera
{
	mat4 Projection;
	mat4 View;
} u_camera;

const float gridSize = 10000.0;
const float gridSpacing = 5.0;

vec3 getVertexPosition(int index)
{
	if (index % 4 <= 1)
	{
		vec3 offset = vec3(0.0, 0.0, gridSpacing) * ((index + 4) / 8) * ((index / 4) % 2 == 0 ? 1 : -1);
		return vec3(gridSize, 0.0, 0.0) * ((index % 4) * 2 - 1) + offset;
	}
	else
	{
		vec3 offset = vec3(gridSpacing, 0.0, 0.0) * ((index + 4) / 8) * ((index / 4) % 2 == 0 ? 1 : -1);
		return vec3(0.0, 0.0, gridSize) * ((index % 4) * 2 - 5) + offset;
	}
}

void main()
{
	pass_position = getVertexPosition(gl_VertexID);
	pass_cameraPosition = (vec4(1.0) * inverse(u_camera.View)).xyz;

	gl_Position = u_camera.Projection * u_camera.View * vec4(pass_position, 1.0);
}
