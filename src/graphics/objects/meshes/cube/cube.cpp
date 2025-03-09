#include "cube.h"

Cube::Cube(Renderer& renderer, int size) {

    float halfSize = size / 2.0f;

    // Définition des 8 sommets partagés
    std::vector<Mesh::Vertex> vertices = {
        {dx::XMFLOAT3(-halfSize, -halfSize, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, -halfSize, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, halfSize, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(-halfSize, halfSize, -halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(-halfSize, -halfSize, halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, -halfSize, halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(halfSize, halfSize, halfSize), dx::XMFLOAT3()},
        {dx::XMFLOAT3(-halfSize, halfSize, halfSize), dx::XMFLOAT3()}
    };

    // Définition des indices pour former les 12 triangles du cube
    std::vector<unsigned short> indices = {
        0, 2, 1,  0, 3, 2,  // Face arrière
        1, 6, 5,  1, 2, 6,  // Face droite
        5, 7, 4,  5, 6, 7,  // Face avant
        4, 3, 0,  4, 7, 3,  // Face gauche
        3, 6, 2,  3, 7, 6,  // Face haut
        4, 1, 5,  4, 0, 1   // Face bas
    };

    this->calculateNormals();
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}

