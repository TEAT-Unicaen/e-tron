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
    float3 finalColor = float3(0, 0, 0);

    // Boucle sur chaque lumière
    for (uint i = 0; i < 2; i++)
    {
        LightBuffer lightBuffer = lightBuffers[i];

        ToL toL = toLight(lightBuffer.lightPosition, input.viewPos);
        const float att = attenuate(lightBuffer.attConst, lightBuffer.attLinear, lightBuffer.attQuad, toL.dist);
        const float3 diffuseV = diffuse(lightBuffer.lightColor, lightBuffer.diffuseIntensity, att, toL.dir, input.viewNormal);
        
        uint z = input.instanceId % width; // Column
        uint x = input.instanceId / width; // Row
        bool isChecker = ((x + z) % 2) == 0;
        finalColor += saturateColor(diffuseV, lightBuffer.ambient, color[isChecker ? 0 : 1]);
    }

    return float4(finalColor, 1.0f);
}


