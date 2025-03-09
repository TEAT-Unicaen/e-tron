#include "transform.hlsli"

struct VSOut {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    float4 position : SV_Position;
};

VSOut main(float3 position : Position, float3 normal : Normal) {
    VSOut output;
    output.viewPos = mul(float4(position, 1.0f), model).xyz;
    output.viewNormal = normalize(mul(normal, (float3x3)model));
    output.position = mul(float4(position, 1.0f), modelViewProjection);
    return output;
}