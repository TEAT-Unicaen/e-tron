#include "cylinderTruncated.h"

CylinderTruncated::CylinderTruncated(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, int slices)
    : Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {

    std::vector<dx::XMFLOAT3> vertices;
    std::vector<unsigned short> indices;

    float radiusSmall = 0.8f;
	float radiusBig = 1.0f;
    float height = 1.0f;
    float angleStep = 2.0f * DirectX::XM_PI / slices;

    // Ajouter les sommets des cercles du haut et du bas
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        
        float xs = radiusSmall * cos(angle);
        float zs = radiusSmall * sin(angle);

		float xb = radiusBig * cos(angle);
		float zb = radiusBig * sin(angle);
        
        //SMALL
        // Point sur le cercle du haut
        vertices.push_back(dx::XMFLOAT3(xs, height / 2, zs));
        // Point sur le cercle du bas
        vertices.push_back(dx::XMFLOAT3(xs, -height / 2, zs));

		//BIG
		// Point sur le cercle du haut
		vertices.push_back(dx::XMFLOAT3(xb, height / 2, zb));
		// Point sur le cercle du bas
		vertices.push_back(dx::XMFLOAT3(xb, -height / 2, zb));
    }

    // Ajouter les centres des cercles (pour les triangles de la base)
    int centerTopIndex = vertices.size();
    vertices.push_back(dx::XMFLOAT3(0, height / 2, 0));

    int centerBottomIndex = vertices.size();
    vertices.push_back(dx::XMFLOAT3(0, -height / 2, 0));

    // Indices pour les faces du cylindre
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % slices;
        
		// cylindre interne
        indices.push_back(i * 4);
        indices.push_back(i * 4 + 1);
        indices.push_back(next * 4);

        indices.push_back(i * 4 + 1);
        indices.push_back(next * 4 + 1);
        indices.push_back(next * 4);
        
        // cylindre externe
        indices.push_back(i * 4 + 3);
        indices.push_back(i * 4 + 2);
        indices.push_back(next * 4 + 2);

        indices.push_back(i * 4 + 3);
        indices.push_back(next * 4 + 2);
        indices.push_back(next * 4 + 3);
        
        // cercle haut
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 3);
        indices.push_back(next * 4 + 1);

        indices.push_back(i * 4 + 3);
        indices.push_back(next * 4 + 3);
        indices.push_back(next * 4 + 1);
        
		// cercle bas
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4);
        indices.push_back(next * 4);

        indices.push_back(i * 4 + 2);
        indices.push_back(next * 4);
        indices.push_back(next * 4 + 2);
        
    }

    this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
    this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));
    this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}