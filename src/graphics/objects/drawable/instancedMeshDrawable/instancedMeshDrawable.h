#pragma once

#include "../drawable.h"
#include "../../meshes/mesh.h"
#include "../../bindable/bindableBase.h"
#include "../../bindable/buffers/instanceBuffer.h"

class InstancedMeshDrawable : public Drawable {  
public:  
   InstancedMeshDrawable(  
       Renderer& renderer,  
       dx::XMFLOAT3 startPosition,  
       dx::XMFLOAT3 startRotation,  
       Mesh& mesh,  
       std::wstring vertexShaderName,  
       std::wstring pixelShaderName  
   );  

   void draw(Renderer& renderer) const noexcept(!IS_DEBUG_MODE) override;  

   InstanceBuffer& getInstanceBuffer() noexcept;  

protected:  
   InstanceBuffer* pInstanceBuffer;  
};