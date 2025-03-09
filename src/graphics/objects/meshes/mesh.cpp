#include "mesh.h"

void Mesh::calculateNormals() {
    // Initialisation des normales à 0
    for (auto& vertex : this->vertices) {
        vertex.normal = { 0.0f, 0.0f, 0.0f };
    }

    // Calcul des normales pour chaque triangle
    for (size_t i = 0; i < this->indices.size(); i += 3) {
        // Récupère les indices des sommets
        auto idx0 = this->indices[i];
        auto idx1 = this->indices[i + 1];
        auto idx2 = this->indices[i + 2];

        // Récupère les positions des sommets
        auto& v0 = this->vertices[idx0];
        auto& v1 = this->vertices[idx1];
        auto& v2 = this->vertices[idx2];

        // Vecteurs des bords du triangle
        dx::XMFLOAT3 edge1 = {
            v1.pos.x - v0.pos.x,
            v1.pos.y - v0.pos.y,
            v1.pos.z - v0.pos.z
        };

        dx::XMFLOAT3 edge2 = {
            v2.pos.x - v0.pos.x,
            v2.pos.y - v0.pos.y,
            v2.pos.z - v0.pos.z
        };

        // Calcul de la normale (produit vectoriel des bords)
        dx::XMFLOAT3 normal = {
            +edge1.y * edge2.z - edge1.z * edge2.y,
            +edge1.z * edge2.x - edge1.x * edge2.z,
            +edge1.x * edge2.y - edge1.y * edge2.x
        };

        // Normalisation de la normale
        dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&normal));
        dx::XMStoreFloat3(&normal, normalVec);

        // Ajout de la normale calculée à chaque sommet
        v0.normal.x += normal.x;
        v0.normal.y += normal.y;
        v0.normal.z += normal.z;

        v1.normal.x += normal.x;
        v1.normal.y += normal.y;
        v1.normal.z += normal.z;

        v2.normal.x += normal.x;
        v2.normal.y += normal.y;
        v2.normal.z += normal.z;
    }

    // Normalisation des normales pour chaque sommet
    for (auto& vertex : vertices) {
        dx::XMVECTOR normalVec = dx::XMVector3Normalize(dx::XMLoadFloat3(&vertex.normal));
        dx::XMStoreFloat3(&vertex.normal, normalVec);
    }
}