#include "cone.h"

Cone::Cone(Renderer& renderer, float radius, float height, UINT slices) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned short> indices;

    size_t slicesSize = static_cast<size_t>(slices);
    vertices.reserve(slicesSize + 2);  // 1 sommet central + 1 sommet par tranche
    indices.reserve(slicesSize * 3 + slicesSize * 3); // 3 indices pour chaque tranche latérale + base

    float angleStep = dx::XM_2PI / slices;
    float halfHeight = height / 2;

    // Sommet central pour la base
    vertices.push_back(Mesh::Vertex{ dx::XMFLOAT3(0, -halfHeight, 0), dx::XMFLOAT3(0, -1, 0) });

    // Sommets du contour du cône
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Calcul de la normale pour le shading Phong (normalise le vecteur)
        dx::XMFLOAT3 normal(x, radius, z);
        dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&normal));
        dx::XMStoreFloat3(&normal, normalVec);

        // Ajouter le sommet pour le contour
        vertices.push_back(Mesh::Vertex{ dx::XMFLOAT3(x, -halfHeight, z), normal });
    }

    // ----- Faces latérales (corps du cône) -----
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Indices pour la face latérale (1 triangle pour chaque tranche)
        indices.push_back(0);        // Sommet central
        indices.push_back(i + 1);    // Sommet actuel
        indices.push_back(next + 1); // Sommet suivant
    }

    // ----- Base du cône (triangle pour chaque section) -----
    unsigned short baseCenterIdx = static_cast<unsigned short>(vertices.size());  // Le sommet central de la base
    vertices.push_back(Mesh::Vertex{ dx::XMFLOAT3(0, halfHeight, 0), dx::XMFLOAT3(0, 1, 0) });  // Ajout sommet de la base

    for (int i = 0; i < slices; ++i) {
        unsigned short next = (i + 1) % slices;

        // On ajoute deux triangles pour la base du cône
        indices.push_back(baseCenterIdx);    // Sommet central de la base
        indices.push_back(next + 1);         // Sommet suivant
        indices.push_back(i + 1);            // Sommet actuel

    }

    // Création des buffers
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices, 0u);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
