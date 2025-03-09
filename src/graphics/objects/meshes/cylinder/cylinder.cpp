#include "cylinder.h"

Cylinder::Cylinder(Renderer& renderer, float radius, float height, UINT slices) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned short> indices;

    size_t slicesSize = static_cast<size_t>(slices);
    vertices.reserve(slicesSize * 2 + 2);  // 2 sommets centraux + 2 vertices par tranche
    indices.reserve(slicesSize * 12);  // 6 indices pour chaque côté * 2 pour les 2 disques

    float angleStep = dx::XM_2PI / slices;
    float halfHeight = height / 2;

    // ----- Disques (Haut et Bas) -----
    // Sommet central du disque du haut
    int topCenterIdx = vertices.size();
    vertices.push_back(Vertex{ dx::XMFLOAT3(0, halfHeight, 0), dx::XMFLOAT3(0, 1, 0) });

    // Sommet central du disque du bas
    int bottomCenterIdx = vertices.size();
    vertices.push_back(Vertex{ dx::XMFLOAT3(0, -halfHeight, 0), dx::XMFLOAT3(0, -1, 0) });

    // Sommets du contour du cylindre
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // Normale calculée à partir du rayon pour Phong Shading
        dx::XMFLOAT3 normal(cos(angle), 0, sin(angle));

        // On ajoute les sommets du contour (haut et bas du cylindre)
        // Le même sommet est utilisé pour les 2 disques pour éviter la duplication
        vertices.push_back(Vertex{ dx::XMFLOAT3(x, halfHeight, z), normal });
        vertices.push_back(Vertex{ dx::XMFLOAT3(x, -halfHeight, z), normal });
    }

    // ----- Faces latérales (corps du cylindre) -----
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;

        // Indices pour la face latérale (2 triangles pour chaque tranche)
        indices.push_back(i * 2 + 2);      // Haut du cylindre
        indices.push_back(next * 2 + 2);   // Haut du cylindre
        indices.push_back(i * 2 + 3);      // Bas du cylindre

        indices.push_back(next * 2 + 2);   // Haut du cylindre
        indices.push_back(next * 2 + 3);   // Bas du cylindre
        indices.push_back(i * 2 + 3);      // Bas du cylindre
    }

    // ----- Disque du haut -----
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;
        indices.push_back(topCenterIdx);
        indices.push_back(next * 2 + 2);
        indices.push_back(i * 2 + 2);
    }

    // ----- Disque du bas -----
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;
        indices.push_back(bottomCenterIdx);
        indices.push_back(i * 2 + 3);
        indices.push_back(next * 2 + 3);
    }

    // Création des buffers
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices, 0u);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
