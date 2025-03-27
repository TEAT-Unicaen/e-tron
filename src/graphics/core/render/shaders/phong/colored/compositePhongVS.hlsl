#include "../../transform.hlsli"

cbuffer ParentBuffer : register(b1)
{
    float4x4 parentModel;
};

struct VSOut
{
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    float4 position : SV_Position;
};

VSOut main(float3 position : Position, float3 normal : Normal)
{
    VSOut output;

    float4 pos4 = float4(position, 1.0f);

    float4x4 realModel = mul(model, parentModel);

    output.viewPos = mul(pos4, realModel).xyz;
    
    output.viewNormal = normalize(mul(normal, (float3x3) realModel));

    float4 worldPosition = mul(pos4, realModel);
    output.position = mul(worldPosition, mul(view, projection));

    return output;
}