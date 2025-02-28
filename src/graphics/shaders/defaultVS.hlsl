#include "transform.hlsli"

float4 main(float3 position : Position) : SV_Position {
    return mul(float4(position, 1.0f), transform);
}