#include "../../transform.hlsli"

struct VSOut
{
    float2 texCoord : TexCoord;
    float4 position : SV_Position;
};

VSOut main(float3 position : Position, float2 texCoord : TexCoord)
{
    VSOut output;
    output.position = mul(float4(position, 1.0f), modelViewProjection);
    output.texCoord = texCoord;
    return output;
}