#include "../../colors.hlsli"
#include "../../phong.hlsli"

struct PSIn {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
};

float4 main(PSIn input) : SV_Target {
    float3 finalDifuse = float3(0, 0, 0);

    // Boucle sur chaque lumière
    for (uint i = 0; i < numLights; i++) {
        LightBuffer lightBuffer = lightBuffers[i];

        ToL toL = toLight(lightBuffer.lightPosition, input.viewPos);
        const float att = attenuate(lightBuffer.attConst, lightBuffer.attLinear, lightBuffer.attQuad, toL.dist);
        const float3 diffuseV = diffuse(lightBuffer.lightColor, lightBuffer.diffuseIntensity, att, toL.dir, input.viewNormal);
        finalDifuse += diffuseV;
    }

    finalDifuse /= float3(numLights, numLights, numLights);

    return saturateColor(finalDifuse, ambient, color[0]);
}

