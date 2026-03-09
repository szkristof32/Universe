#include "MeshGenerator.h"

#include <glm/ext/scalar_constants.hpp>

using namespace UniverseEngine;

constexpr static uint32_t s_HorizontalResoltion = 20;
constexpr static uint32_t s_VerticalResoltion = 20;

Mesh MeshGenerator::GenerateSphere()
{
	std::vector<Vertex> vertices;

	auto v0 = Vertex{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } };
	vertices.emplace_back(v0);

	for (uint32_t i = 0; i < s_HorizontalResoltion - 1; i++)
	{
		float phi = glm::pi<float>() * static_cast<float>(i + 1) / static_cast<float>(s_HorizontalResoltion);
		for (uint32_t j = 0; j < s_VerticalResoltion; j++)
		{
			float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(s_VerticalResoltion);
			float x = glm::sin(phi) * glm::cos(theta);
			float y = glm::cos(phi);
			float z = glm::sin(phi) * glm::sin(theta);

			Vertex vertex{};
			vertex.Position = glm::vec3(x, y, z);
			vertex.Normal = glm::vec3(x, y, z);

			vertices.emplace_back(std::move(vertex));
		}
	}

	auto v1 = Vertex{ { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } };
	vertices.emplace_back(v1);

	std::vector<uint32_t> indices;

	for (uint32_t i = 0; i < s_VerticalResoltion; ++i)
	{
		uint32_t i0 = i + 1;
		uint32_t i1 = (i + 1) % s_VerticalResoltion + 1;

		indices.emplace_back(0);
		indices.emplace_back(i1);
		indices.emplace_back(i0);

		i0 = i + s_VerticalResoltion * (s_HorizontalResoltion - 2) + 1;
		i1 = (i + 1) % s_VerticalResoltion + s_VerticalResoltion * (s_HorizontalResoltion - 2) + 1;

		indices.emplace_back(static_cast<uint32_t>(vertices.size()) - 1);
		indices.emplace_back(i0);
		indices.emplace_back(i1);
	}

	for (uint32_t j = 0; j < s_HorizontalResoltion - 2; j++)
	{
		uint32_t j0 = j * s_VerticalResoltion + 1;
		uint32_t j1 = (j + 1) * s_VerticalResoltion + 1;

		for (uint32_t i = 0; i < s_VerticalResoltion; i++)
		{
			uint32_t i0 = j0 + i;
			uint32_t i1 = j0 + (i + 1) % s_VerticalResoltion;
			uint32_t i2 = j1 + (i + 1) % s_VerticalResoltion;
			uint32_t i3 = j1 + i;

			indices.emplace_back(i0);
			indices.emplace_back(i1);
			indices.emplace_back(i2);

			indices.emplace_back(i2);
			indices.emplace_back(i3);
			indices.emplace_back(i0);

		}
	}

	return Mesh(vertices, indices);
}
