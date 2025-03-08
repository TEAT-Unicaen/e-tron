#include "doubleTore.h"  

DoubleTore::DoubleTore(Renderer& renderer, dx::XMFLOAT3 startPosition, dx::XMFLOAT3 startRotation, dx::XMFLOAT3 velocity, dx::XMFLOAT3 angularVelocity, std::array<Color, 1> colors) {
   dx::XMFLOAT3 offset = { 0.5f, 0.0f, 0.0f };

   // Convert XMFLOAT3 to XMVECTOR for addition  
   DirectX::XMVECTOR startPosVec = DirectX::XMLoadFloat3(&startPosition);  
   DirectX::XMVECTOR offsetVec = DirectX::XMLoadFloat3(&offset);  

   // Perform addition  
   DirectX::XMVECTOR newPosVec1 = DirectX::XMVectorAdd(startPosVec, offsetVec);  
   DirectX::XMVECTOR newPosVec2 = DirectX::XMVectorSubtract(startPosVec, offsetVec);  

   // Convert back to XMFLOAT3  
   DirectX::XMFLOAT3 newPos1;  
   DirectX::XMFLOAT3 newPos2;  
   DirectX::XMStoreFloat3(&newPos1, newPosVec1);
   DirectX::XMStoreFloat3(&newPos2, newPosVec2);

   this->add(std::make_unique<ColoredTore>(renderer, newPos1, startRotation, velocity, angularVelocity, colors));  
   this->add(std::make_unique<ColoredTore>(renderer, newPos2, startRotation, velocity, angularVelocity, colors));  
}