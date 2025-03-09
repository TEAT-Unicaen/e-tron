#include "cube.h"
Cube::Cube(Renderer& renderer, int size) {
    float halfSize = size / 2.0f;
    
    // Définition des sommets avec normales
    // Nous devons utiliser des sommets distincts pour chaque face
    // car les normales diffèrent selon la face
    std::vector<Mesh::Vertex> vertices = {
        // Face arrière (-Z) - Normale (0,0,-1)
        {dx::XMFLOAT3(-halfSize, -halfSize, -halfSize), dx::XMFLOAT3(0.0f, 0.0f, -1.0f)},
        {dx::XMFLOAT3(halfSize, -halfSize, -halfSize), dx::XMFLOAT3(0.0f, 0.0f, -1.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, -halfSize), dx::XMFLOAT3(0.0f, 0.0f, -1.0f)},
        {dx::XMFLOAT3(-halfSize, halfSize, -halfSize), dx::XMFLOAT3(0.0f, 0.0f, -1.0f)},
        
        // Face avant (+Z) - Normale (0,0,1)
        {dx::XMFLOAT3(-halfSize, -halfSize, halfSize), dx::XMFLOAT3(0.0f, 0.0f, 1.0f)},
        {dx::XMFLOAT3(halfSize, -halfSize, halfSize), dx::XMFLOAT3(0.0f, 0.0f, 1.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, halfSize), dx::XMFLOAT3(0.0f, 0.0f, 1.0f)},
        {dx::XMFLOAT3(-halfSize, halfSize, halfSize), dx::XMFLOAT3(0.0f, 0.0f, 1.0f)},
        
        // Face droite (+X) - Normale (1,0,0)
        {dx::XMFLOAT3(halfSize, -halfSize, -halfSize), dx::XMFLOAT3(1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, -halfSize, halfSize), dx::XMFLOAT3(1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, halfSize), dx::XMFLOAT3(1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, -halfSize), dx::XMFLOAT3(1.0f, 0.0f, 0.0f)},
        
        // Face gauche (-X) - Normale (-1,0,0)
        {dx::XMFLOAT3(-halfSize, -halfSize, -halfSize), dx::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(-halfSize, -halfSize, halfSize), dx::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(-halfSize, halfSize, halfSize), dx::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
        {dx::XMFLOAT3(-halfSize, halfSize, -halfSize), dx::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
        
        // Face supérieure (+Y) - Normale (0,1,0)
        {dx::XMFLOAT3(-halfSize, halfSize, -halfSize), dx::XMFLOAT3(0.0f, 1.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, -halfSize), dx::XMFLOAT3(0.0f, 1.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, halfSize, halfSize), dx::XMFLOAT3(0.0f, 1.0f, 0.0f)},
        {dx::XMFLOAT3(-halfSize, halfSize, halfSize), dx::XMFLOAT3(0.0f, 1.0f, 0.0f)},
        
        // Face inférieure (-Y) - Normale (0,-1,0)
        {dx::XMFLOAT3(-halfSize, -halfSize, -halfSize), dx::XMFLOAT3(0.0f, -1.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, -halfSize, -halfSize), dx::XMFLOAT3(0.0f, -1.0f, 0.0f)},
        {dx::XMFLOAT3(halfSize, -halfSize, halfSize), dx::XMFLOAT3(0.0f, -1.0f, 0.0f)},
        {dx::XMFLOAT3(-halfSize, -halfSize, halfSize), dx::XMFLOAT3(0.0f, -1.0f, 0.0f)}
    };
    
    // Définition des indices pour les triangles
    // Maintenant que nous avons 24 sommets (4 par face)
    std::vector<unsigned short> indices = {
        // Face arrière
        0, 2, 1,  0, 3, 2,
        // Face avant
        4, 5, 6,  4, 6, 7,
        // Face droite
        8, 10, 9,  8, 11, 10,
        // Face gauche
        12, 13, 14,  12, 14, 15,
        // Face supérieure
        16, 18, 17,  16, 19, 18,
        // Face inférieure
        20, 21, 22,  20, 22, 23
    };
    
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}