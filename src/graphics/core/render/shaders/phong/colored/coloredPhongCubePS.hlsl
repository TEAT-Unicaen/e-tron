#include "../../colors.hlsli"
#include "../../phong.hlsli"

struct PSIn {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
};

float4 main(PSIn input, uint tid : SV_PrimitiveID) : SV_Target
{
    float3 finalColor = float3(0, 0, 0);

    // Boucle sur chaque lumière
    for (uint i = 0; i < 2; i++)
    {
        LightBuffer lightBuffer = lightBuffers[i];

        ToL toL = toLight(lightBuffer.lightPosition, input.viewPos);
        const float att = attenuate(lightBuffer.attConst, lightBuffer.attLinear, lightBuffer.attQuad, toL.dist);
        const float3 diffuseV = diffuse(lightBuffer.lightColor, lightBuffer.diffuseIntensity, att, toL.dir, input.viewNormal);
        finalColor += saturateColor(diffuseV, lightBuffer.ambient, color[(tid / 2) % colorCount]);
    }

    return float4(finalColor, 1.0f);
}