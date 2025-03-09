#include "pyramid.h"

Pyramid::Pyramid(Renderer& renderer, int size) {
    float halfSize = size / 2.0f;

    // Définition des sommets (en utilisant des sommets partagés)
    std::vector<Mesh::Vertex> vertices = {
        // Base (Y = 0) - Uniques pour chaque triangle
        {dx::XMFLOAT3(-halfSize, 0.0f, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, 0.0f, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(-halfSize, 0.0f, halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, 0.0f, halfSize), dx::XMFLOAT3()},

        // Point sommet de la pyramide
        {dx::XMFLOAT3(0.0f, size, 0.0f), dx::XMFLOAT3()}
    };

    // Définition des indices pour les faces de la pyramide
    std::vector<unsigned short> indices = {
        // Base (2 triangles)
        0, 1, 2,    2, 1, 3,

        // Faces latérales
        0, 4, 1,   // Face avant
        1, 4, 3,   // Face droite
        3, 4, 2,   // Face arrière
        2, 4, 0    // Face gauche
    };

    // Appliquer le calcul des normales sur les sommets du cube
    this->calculateNormals();

    // Initialiser les buffers après le calcul des normales
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
