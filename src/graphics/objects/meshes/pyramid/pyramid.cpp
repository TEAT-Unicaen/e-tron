#include "pyramid.h"

Pyramid::Pyramid(Renderer& renderer, int size) {
    float halfSize = size / 2.0f;

    // Calcul exact des normales pour une pyramide à base carrée
    // La valeur exacte pour sqrt(5) utilisée dans la normalisation
    const float sqrt5 = std::sqrtf(5.0f);

    // Valeurs normalisées exactes (stockées dans des variables)
    const float lateralY = 2.0f / sqrt5;  // ≈ 0.4472135955
    const float lateralXZ = 1.0f / sqrt5; // ≈ 0.8944271910

    // Normales pour chaque face
    const dx::XMFLOAT3 normalBase(0.0f, -1.0f, 0.0f);          // Base (Y-)
    const dx::XMFLOAT3 normalFront(0.0f, lateralY, lateralXZ); // Face avant (Z+)
    const dx::XMFLOAT3 normalRight(lateralXZ, lateralY, 0.0f); // Face droite (X+)
    const dx::XMFLOAT3 normalBack(0.0f, lateralY, -lateralXZ); // Face arrière (Z-)
    const dx::XMFLOAT3 normalLeft(-lateralXZ, lateralY, 0.0f); // Face gauche (X-)

    // Définition des sommets avec normales calculées
    std::vector<Mesh::Vertex> vertices = {
        // Base (Y = 0)
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), normalBase},
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), normalBase},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), normalBase},
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), normalBase},

        // Face avant (Z+)
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), normalFront},
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), normalFront},
        {dx::XMFLOAT3(0.0f, size, 0.0f), normalFront},

        // Face droite (X+)
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), normalRight},
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), normalRight},
        {dx::XMFLOAT3(0.0f, size, 0.0f), normalRight},

        // Face arrière (Z-)
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), normalBack},
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), normalBack},
        {dx::XMFLOAT3(0.0f, size, 0.0f), normalBack},

        // Face gauche (X-)
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), normalLeft},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), normalLeft},
        {dx::XMFLOAT3(0.0f, size, 0.0f), normalLeft}
    };

    // Définition des indices pour former les triangles
    std::vector<unsigned short> indices = {
        // Base (2 triangles)
        0, 1, 2,
        1, 3, 2,

        // 4 faces latérales triangulaires
        4, 5, 6,  // Face avant
        7, 8, 9,  // Face droite
        10, 11, 12, // Face arrière
        13, 14, 15  // Face gauche
    };

    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}