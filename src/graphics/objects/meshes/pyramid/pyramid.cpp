#include "pyramid.h"

Pyramid::Pyramid(Renderer& renderer, int size) {
    float angle = 1.0f / std::sqrtf(2);

	float halfSize = size / 2.0f;

    std::vector<Mesh::Vertex> vertices = {
        // Base (Y = 0) - Unique vertices per triangle
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), dx::XMFLOAT3(0, -1, 0)},

        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), dx::XMFLOAT3(0, -1, 0)},

        // Face avant
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), dx::XMFLOAT3(0, angle, -angle)},
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), dx::XMFLOAT3(0, angle, -angle)},
        {dx::XMFLOAT3(0.0f, size, 0.0f), dx::XMFLOAT3(0, angle, -angle)},

        // Face droite
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), dx::XMFLOAT3(angle, angle, 0)},
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), dx::XMFLOAT3(angle, angle, 0)},
        {dx::XMFLOAT3(0.0f, size, 0.0f), dx::XMFLOAT3(angle, angle, 0)},

        // Face arrière
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), dx::XMFLOAT3(0, angle, angle)},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), dx::XMFLOAT3(0, angle, angle)},
        {dx::XMFLOAT3(0.0f, size, 0.0f), dx::XMFLOAT3(0, angle, angle)},

        // Face gauche
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), dx::XMFLOAT3(-angle, angle, 0)},
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), dx::XMFLOAT3(-angle, angle, 0)},
        {dx::XMFLOAT3(0.0f, size, 0.0f), dx::XMFLOAT3(-angle, angle, 0)}
    };


	std::vector<unsigned short> indices = {
		// Base (two triangles)
		0, 1, 2,  3, 4, 5,

		// Sides
		6, 8, 7,   // Front face
		9, 11, 10, // Right face
		12, 14, 13, // Back face
		15, 17, 16  // Left face
	};

	this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
	this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
