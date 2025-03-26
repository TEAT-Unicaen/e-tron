#include "../../transform.hlsli"

struct VSOut {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    float4 position : SV_Position;
};

VSOut main(float3 position : Position, float3 normal : Normal) {
    float4 pos4 = float4(position, 1.0f);
    float4x4 modelViewProjection = mul(model, mul(view, projection));
    VSOut output;
    float4x4 modelView = mul(model, view);
    output.viewPos = mul(pos4, modelView).xyz;
    output.viewNormal = normalize(mul(normal, (float3x3)modelView));
    output.position = mul(pos4, modelViewProjection);
    return output;
}