#include "../../transform.hlsli"

struct VSOut
{
    float2 texCoord : TexCoord;
    float4 position : SV_Position;
};

struct VSIn
{
    float3 position : Position;
    float2 texCoord : TexCoord;
};

VSOut main(VSIn input) {
    float4x4 modelViewProjection = mul(model, mul(view, projection));
    VSOut output;
    output.position = mul(float4(input.position, 1.0f), modelViewProjection);
    output.texCoord = input.texCoord;
    return output;
}