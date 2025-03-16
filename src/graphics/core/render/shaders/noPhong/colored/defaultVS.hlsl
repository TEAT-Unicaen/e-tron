#include "../../transform.hlsli"

float4 main(float3 position : Position) : SV_Position {
    float4x4 modelViewProjection = mul(model, mul(view, projection));
    return mul(float4(position, 1.0f), modelViewProjection);
}