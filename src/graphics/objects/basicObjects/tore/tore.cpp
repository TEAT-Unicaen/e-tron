#include "tore.h"

Tore::Tore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity)
    : Drawable(renderer, startPosition, startRotation, velocity, angularVelocity) {

    struct Vertex {
        dx::XMFLOAT3 pos;
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned short> indices;

    float innerRadius = 0.25f;
    float outerRadius = 0.5f;

    UINT slices = 40;  // Major ring segments
    UINT stacks = 20;  // Tube segments

    float thetaStep = 2.0f * dx::XM_PI / slices;
    float phiStep = 2.0f * dx::XM_PI / stacks;

    // Generate vertices
    for (UINT i = 0; i <= slices; i++) {
        float theta = i * thetaStep;

        for (UINT j = 0; j <= stacks; j++) {
            float phi = j * phiStep;

            float x = (outerRadius + innerRadius * std::cos(phi)) * std::cos(theta);
            float y = innerRadius * std::sin(phi);
            float z = (outerRadius + innerRadius * std::cos(phi)) * std::sin(theta);

            vertices.push_back({ dx::XMFLOAT3(x, y, z) });
        }
    }

    // Generate indices for the torus
    for (UINT i = 0; i < slices; i++) {
        for (UINT j = 0; j < stacks; j++) {
            UINT nextI = (i + 1) % slices;
            UINT nextJ = (j + 1) % stacks;

            // First triangle
            indices.push_back(i * (stacks + 1) + j);
            indices.push_back(nextI * (stacks + 1) + j);
            indices.push_back(i * (stacks + 1) + nextJ);

            // Second triangle
            indices.push_back(i * (stacks + 1) + nextJ);
            indices.push_back(nextI * (stacks + 1) + j);
            indices.push_back(nextI * (stacks + 1) + nextJ);
        }
    }

    // Bind data to GPU
    this->addBindable(std::make_shared<VertexBuffer>(renderer, vertices));
    this->addBindable(std::make_shared<IndexBuffer>(renderer, indices));
    auto pvs = std::make_shared<VertexShader>(renderer, L"defaultVS");
    auto pvsbc = pvs->getBytecode();
    this->addBindable(std::move(pvs));
    const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
    {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
    this->addBindable(std::make_shared<Topology>(renderer, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    this->addBindable(std::make_shared<TransformConstantBuffer>(renderer, *this));
}
