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
    float4x4 realModel = mul(model, parentModel);
    float4x4 realModelViewProjection = mul(realModel, mul(view, projection));
    
    VSOut output;    
    output.viewPos = mul(float4(position, 1.0f), realModel).xyz;
    output.viewNormal = normalize(mul(normal, (float3x3) realModel));
    output.position = mul(float4(position, 1.0f), realModelViewProjection);
    return output;
}