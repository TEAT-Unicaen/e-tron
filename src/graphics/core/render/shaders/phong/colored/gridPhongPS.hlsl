#include "../../colors.hlsli"
#include "../../phong.hlsli"

cbuffer InstanceBuffer : register(b2)
{
    uint length;
    uint width;
};

struct PSIn {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    uint instanceId : InstanceID;
};

float4 main(PSIn input, float4 svPos : SV_Position) : SV_Target
{
    float3 finalDifuse = float3(0, 0, 0);

    // Boucle sur chaque lumière
    for (uint i = 0; i < numLights; i++){
        LightBuffer lightBuffer = lightBuffers[i];

        ToL toL = toLight(lightBuffer.lightPosition, input.viewPos);
        const float att = attenuate(lightBuffer.attConst, lightBuffer.attLinear, lightBuffer.attQuad, toL.dist);
        const float3 diffuseV = diffuse(lightBuffer.lightColor, lightBuffer.diffuseIntensity, att, toL.dir, input.viewNormal);
        finalDifuse += diffuseV;
    }

    finalDifuse /= float3(numLights, numLights, numLights);
    
    
    uint z = input.instanceId % width; // Column
    uint x = input.instanceId / width; // Row
    bool isChecker = ((x + z) % 2) == 0;
    return saturateColor(finalDifuse, ambient, color[isChecker ? 0 : 1]);
}


