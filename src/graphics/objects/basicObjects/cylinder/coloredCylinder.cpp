#include "coloredCylinder.h"

ColoredCylinder::ColoredCylinder(
    Renderer& renderer,
    dx::XMFLOAT3 startPosition,
    dx::XMFLOAT3 startRotation,
    dx::XMFLOAT3 velocity,
    dx::XMFLOAT3 angularVelocity,
    std::array<Color, 3>& colors)

    : Cylinder(renderer, startPosition, startRotation, velocity, angularVelocity), colors(colors) {

    auto pvs = shaderManager.getVertexShader(L"defaultVS");
    auto pvsbc = pvs->getBytecode();
    this->addBindable(std::move(pvs));

    this->addBindable(shaderManager.getPixelShader(L"coloredCylinderPS"));
    
    struct ColorBuffer {
        dx::XMFLOAT4 colors[3];
    };

    const ColorBuffer cb = {
        {
            this->colors[0].toFloat4(),  // Couleur du haut
            this->colors[1].toFloat4(),  // Couleur du bas
            this->colors[2].toFloat4()   // Couleur des faces latérales
        }
    };
    this->addBindable(std::make_shared<PixelConstantBuffer<ColorBuffer>>(renderer, cb, 0u));

    const std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc = {
        {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    this->addBindable(std::make_shared<InputLayout>(renderer, inputElementDesc, pvsbc));
}
