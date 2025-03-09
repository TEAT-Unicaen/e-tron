#include "tore.h"

Tore::Tore(Renderer& renderer, float outrerRadius, float innerRadius, UINT sliceCount, UINT stackCount) {
    std::vector<Vertex> vertices;
    std::vector<unsigned short> indices;

    // Réservation de la mémoire pour éviter des reallocations
	size_t sliceCountSize = static_cast<size_t>(sliceCount);
	size_t stackCountSize = static_cast<size_t>(stackCount);
    vertices.reserve((sliceCountSize + 1) * (stackCountSize + 1));  // un sommet par intersection
    indices.reserve(sliceCountSize * stackCountSize * 6);  // 6 indices par face (2 triangles)

    // Boucle pour les stacks
    for (UINT i = 0; i <= stackCount; i++) {
        float phi = dx::XM_2PI * i / stackCount;  // latitude [0, 2*pi]

        // Boucle pour les slices
        for (UINT j = 0; j <= sliceCount; j++) {
            float theta = 2.0f * dx::XM_PI * j / sliceCount;  // longitude [0, 2*pi]

            // Position des sommets
            dx::XMFLOAT3 position = {
                (outrerRadius + innerRadius * std::cos(phi)) * std::cos(theta),
                innerRadius * std::sin(phi),
                (outrerRadius + innerRadius * std::cos(phi)) * std::sin(theta)
            };

            // Normal
            dx::XMFLOAT3 normal = {
                std::cos(phi) * std::cos(theta),
                std::sin(phi),
                std::cos(phi) * std::sin(theta)
            };
            dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&normal));
            dx::XMStoreFloat3(&normal, normalVec);

            // Ajout du vertex
            vertices.push_back(Vertex{ position, normal });
        }
    }

    // Génération des indices pour les faces
    for (UINT i = 0; i < stackCount; i++) {
        for (UINT j = 0; j < sliceCount; j++) {
            unsigned short topLeft = i * (sliceCount + 1) + j;
            unsigned short bottomLeft = (i + 1) * (sliceCount + 1) + j;
            unsigned short topRight = i * (sliceCount + 1) + j + 1;
            unsigned short bottomRight = (i + 1) * (sliceCount + 1) + j + 1;

            // Première face du quadrilatère (2 triangles)
            indices.push_back(topLeft);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);

            indices.push_back(topRight);
            indices.push_back(bottomRight);
            indices.push_back(bottomLeft);
        }
    }

    // Création des buffers
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
