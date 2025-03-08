#include "cylinder.h"

Cylinder::Cylinder(Renderer& renderer, float radius, float height, UINT slices) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned short> indices;

	
    // Réservation de mémoire pour éviter les reallocations dynamiques
    size_t slicesSize = static_cast<size_t>(slices);
    vertices.reserve(slicesSize * 10 + 2);
    indices.reserve(slicesSize * 12);
    float angleStep = dx::XM_2PI / slices;
    float halfHeight = height / 2;

    // ----- Faces latérales -----
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float nextAngle = ((i + 1) % slices) * angleStep;

        float x1 = radius * cos(angle);
        float z1 = radius * sin(angle);
        float x2 = radius * cos(nextAngle);
        float z2 = radius * sin(nextAngle);

        dx::XMFLOAT3 normal1(cos(angle), 0, sin(angle));
        dx::XMFLOAT3 normal2(cos(nextAngle), 0, sin(nextAngle));

        int baseIdx = vertices.size();

        vertices.push_back({ dx::XMFLOAT3(x1, halfHeight, z1), normal1 });
        vertices.push_back({ dx::XMFLOAT3(x2, halfHeight, z2), normal2 });
        vertices.push_back({ dx::XMFLOAT3(x1, -halfHeight, z1), normal1 });

        vertices.push_back({ dx::XMFLOAT3(x1, -halfHeight, z1), normal1 });
        vertices.push_back({ dx::XMFLOAT3(x2, halfHeight, z2), normal2 });
        vertices.push_back({ dx::XMFLOAT3(x2, -halfHeight, z2), normal2 });

        indices.push_back(baseIdx);
        indices.push_back(baseIdx + 1);
        indices.push_back(baseIdx + 2);
        indices.push_back(baseIdx + 3);
        indices.push_back(baseIdx + 4);
        indices.push_back(baseIdx + 5);
    }

    // ----- Disque du haut -----
    int topCenterIdx = vertices.size();
    vertices.push_back({ dx::XMFLOAT3(0, halfHeight, 0), dx::XMFLOAT3(0, 1, 0) });

    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float nextAngle = ((i + 1) % slices) * angleStep;
        float x1 = radius * cos(angle);
        float z1 = radius * sin(angle);
        float x2 = radius * cos(nextAngle);
        float z2 = radius * sin(nextAngle);

        int idx = vertices.size();
        vertices.push_back({ dx::XMFLOAT3(x1, halfHeight, z1), dx::XMFLOAT3(0, 1, 0) });
        vertices.push_back({ dx::XMFLOAT3(x2, halfHeight, z2), dx::XMFLOAT3(0, 1, 0) });

        indices.push_back(topCenterIdx);
        indices.push_back(idx + 1);
        indices.push_back(idx);

    }

    // ----- Disque du bas -----
    int bottomCenterIdx = vertices.size();
    vertices.push_back({ dx::XMFLOAT3(0, -halfHeight, 0), dx::XMFLOAT3(0, -1, 0) });

    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float nextAngle = ((i + 1) % slices) * angleStep;
        float x1 = radius * cos(angle);
        float z1 = radius * sin(angle);
        float x2 = radius * cos(nextAngle);
        float z2 = radius * sin(nextAngle);

        int idx = vertices.size();
        vertices.push_back({ dx::XMFLOAT3(x1, -halfHeight, z1), dx::XMFLOAT3(0, -1, 0) });
        vertices.push_back({ dx::XMFLOAT3(x2, -halfHeight, z2), dx::XMFLOAT3(0, -1, 0) });

        indices.push_back(bottomCenterIdx);
        indices.push_back(idx);
        indices.push_back(idx + 1);
    }

    // Création des buffers
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
