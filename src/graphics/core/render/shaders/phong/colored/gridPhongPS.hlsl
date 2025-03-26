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
    float specularIntensity;
    float shininess;
};

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
    ToL toL = toLight(lightPosition, input.viewPos);

    const float att = attenuate(attConst, attLinear, attQuad, toL.dist);
    
    const float3 diffuseV = diffuse(lightColor, diffuseIntensity, att, toL.dir, input.viewNormal);
    
    uint z = input.instanceId % width; // Column
    uint x = input.instanceId / width; // Row
    
    // Simple checkerboard pattern - alternating cells
    bool isChecker = ((x + z) % 2) == 0;

    return saturateColor(diffuseV, ambient, color[isChecker ? 0 : 1]);
}


