#include "cylinder.h"

#include <DirectXMath.h>

Cylinder::Cylinder(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, int slices)
    : Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {

    std::vector<dx::XMFLOAT3> vertices;
    std::vector<unsigned short> indices;

    float radius = 0.5f;
    float height = 1.0f;
    float angleStep = 2.0f * DirectX::XM_PI / slices;

    // Ajouter les sommets des cercles du haut et du bas
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Point sur le cercle du haut
        vertices.push_back(dx::XMFLOAT3(x, height / 2, z));

        // Point sur le cercle du bas
        vertices.push_back(dx::XMFLOAT3(x, -height / 2, z));
    }

    // Ajouter les centres des cercles (pour les triangles de la base)
    int centerTopIndex = vertices.size();
    vertices.push_back(dx::XMFLOAT3(0, height / 2, 0));

    int centerBottomIndex = vertices.size();
    vertices.push_back(dx::XMFLOAT3(0, -height / 2, 0));

    // Indices pour les faces du cylindre
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Face latérale (deux triangles)
        indices.push_back(i * 2);
        indices.push_back(next * 2);
        indices.push_back(i * 2 + 1);

        indices.push_back(i * 2 + 1);
        indices.push_back(next * 2);
        indices.push_back(next * 2 + 1);

        // Triangle du haut
        indices.push_back(centerTopIndex);
        indices.push_back(next * 2);
        indices.push_back(i * 2);
        
        // Triangle du bas
        indices.push_back(centerBottomIndex);
        indices.push_back(i * 2 + 1);
        indices.push_back(next * 2 + 1);
    }

    this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
    this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));
    this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}