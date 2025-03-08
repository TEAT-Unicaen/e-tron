#include "cube.h"

Cube::Cube(Renderer& renderer, int size) {

	float realSize = size / 2.0f;

    std::vector<Mesh::Vertex> vertices = {
        // Front Face (Z = -0.5)
        {dx::XMFLOAT3(-realSize, -realSize, -realSize), dx::XMFLOAT3(0, 0, -1)},
        {dx::XMFLOAT3(realSize, -realSize, -realSize), dx::XMFLOAT3(0, 0, -1)},
        {dx::XMFLOAT3(-realSize, realSize, -realSize), dx::XMFLOAT3(0, 0, -1)},
        {dx::XMFLOAT3(realSize, realSize, -realSize), dx::XMFLOAT3(0, 0, -1)},

        // Back Face (Z = 0.5)
        {dx::XMFLOAT3(-realSize, -realSize, realSize), dx::XMFLOAT3(0, 0, 1)},
        {dx::XMFLOAT3(realSize, -realSize, realSize), dx::XMFLOAT3(0, 0, 1)},
        {dx::XMFLOAT3(-realSize, realSize, realSize), dx::XMFLOAT3(0, 0, 1)},
        {dx::XMFLOAT3(realSize, realSize, realSize), dx::XMFLOAT3(0, 0, 1)},

        // Left Face (X = -0.5)
        {dx::XMFLOAT3(-realSize, -realSize, -realSize), dx::XMFLOAT3(-1, 0, 0)},
        {dx::XMFLOAT3(-realSize, realSize, -realSize), dx::XMFLOAT3(-1, 0, 0)},
        {dx::XMFLOAT3(-realSize, -realSize, realSize), dx::XMFLOAT3(-1, 0, 0)},
        {dx::XMFLOAT3(-realSize, realSize, realSize), dx::XMFLOAT3(-1, 0, 0)},

        // Right Face (X = 0.5)
        {dx::XMFLOAT3(realSize, -realSize, -realSize), dx::XMFLOAT3(1, 0, 0)},
        {dx::XMFLOAT3(realSize, realSize, -realSize), dx::XMFLOAT3(1, 0, 0)},
        {dx::XMFLOAT3(realSize, -realSize, realSize), dx::XMFLOAT3(1, 0, 0)},
        {dx::XMFLOAT3(realSize, realSize, realSize), dx::XMFLOAT3(1, 0, 0)},
        
        // Top Face (Y = 0.5)
        {dx::XMFLOAT3(-realSize, realSize, -realSize), dx::XMFLOAT3(0, 1, 0)},
        {dx::XMFLOAT3(realSize, realSize, -realSize), dx::XMFLOAT3(0, 1, 0)},
        {dx::XMFLOAT3(-realSize, realSize, realSize), dx::XMFLOAT3(0, 1, 0)},
        {dx::XMFLOAT3(realSize, realSize, realSize), dx::XMFLOAT3(0, 1, 0)},

        // Bottom Face (Y = -0.5)
        {dx::XMFLOAT3(-realSize, -realSize, -realSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(realSize, -realSize, -realSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(-realSize, -realSize, realSize), dx::XMFLOAT3(0, -1, 0)},
        {dx::XMFLOAT3(realSize, -realSize, realSize), dx::XMFLOAT3(0, -1, 0)}
    };

    std::vector<unsigned short> indices = {
		0, 2, 1,    2, 3, 1, // Front face
		4, 5, 6,    6, 5, 7, // Back face
		8, 10, 9,   10, 11, 9, // Left face
		12, 13, 14, 14, 13, 15, // Right face
		16, 18, 17, 18, 19, 17, // Top face
		20, 21, 22, 22, 21, 23 // Bottom face
	};

	this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);// TODO: slot
	this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}

