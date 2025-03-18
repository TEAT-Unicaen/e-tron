#include "../../colors.hlsli"
#include "../../phong.hlsli"

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

struct PSIn
{
    float3 viewPos : Position;
    float3 viewNormal : Normal;
};

float4 main(PSIn input, uint tid : SV_PrimitiveID) : SV_Target
{
    ToL toL = toLight(lightPosition, input.viewPos);

    const float att = attenuate(attConst, attLinear, attQuad, toL.dist);
    
    const float3 diffuseV = diffuse(lightColor, diffuseIntensity, att, toL.dir, input.viewNormal);
    
    return saturateColor(diffuseV, ambient, color[(tid / 2) % colorCount]);
}