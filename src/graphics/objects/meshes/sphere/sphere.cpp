#include "sphere.h"

Sphere::Sphere(Renderer& renderer, float radius, UINT sliceCount, UINT stackCount) {
	// Vertex buffer
	std::vector<Vertex> vertices;
	vertices.reserve((sliceCount + 1) * (stackCount + 1));
	for (UINT i = 0; i <= stackCount; i++) {
		float phi = dx::XM_PI * i / stackCount;  // Fix: Full latitude range [0, π]
		for (UINT j = 0; j <= sliceCount; j++) {
			float theta = 2.0f * dx::XM_PI * j / sliceCount;

			//Position
			dx::XMFLOAT3 position = {
				radius * std::sin(phi) * std::cos(theta),
				radius * std::cos(phi),
				radius * std::sin(phi) * std::sin(theta)
			};

			// Normal
			dx::XMFLOAT3 normal = {
				std::sin(phi) * std::cos(theta),
				std::cos(phi),
				std::sin(phi) * std::sin(theta)
			};

			dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&normal));
			dx::XMStoreFloat3(&normal, normalVec);

            vertices.emplace_back(Vertex{position, normal});
		}
	}

	// Generate indices
	std::vector<unsigned short> indices;
	indices.reserve(sliceCount * stackCount * 6);
	for (UINT i = 0; i < stackCount; i++) {
		for (UINT j = 0; j < sliceCount; j++) {
			unsigned short topLeft = i * (sliceCount + 1) + j;
			unsigned short bottomLeft = (i + 1) * (sliceCount + 1) + j;
			unsigned short topRight = i * (sliceCount + 1) + j + 1;
			unsigned short bottomRight = (i + 1) * (sliceCount + 1) + j + 1;

			// First Triangle
			indices.emplace_back(topLeft);
			indices.emplace_back(topRight);
			indices.emplace_back(bottomLeft);


			// Second Triangle
			indices.emplace_back(topRight);
			indices.emplace_back(bottomRight);
			indices.emplace_back(bottomLeft);

		}
	}

		this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices, 0u);
		this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}