#include "colors.hlsli"

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
    return color[(tid / 2) % colorCount];
}