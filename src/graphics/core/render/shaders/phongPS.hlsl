#include "colors.hlsli"

cbuffer LightBuffer : register(b1)
{
    float3 lightPosition;
    float3 lightColor;
    float3 ambient;
    float diffuseIntensity;
    float attConst;
    float attLinear;
    float attQuad;
};

struct PSIn {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
};

float4 main(PSIn input) : SV_Target {
    const float3 vToL = lightPosition - input.viewPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

    const float att = 1.0f / (attConst + attLinear * distToL + attQuad * (distToL * distToL));
    
    const float3 diffuse = lightColor * diffuseIntensity * att * max(0.0f, dot(dirToL, input.viewNormal));
    return float4(saturate(diffuse + ambient), 1.0f) * color[0];
}