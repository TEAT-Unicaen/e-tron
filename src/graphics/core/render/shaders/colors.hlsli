#ifndef __COLORS_HLSLI__
#define __COLORS_HLSLI__

#include "macro.hlsli"

cbuffer colors : register(b0)
{
    float4 color[10];
    uint colorCount;
    float padding[3];
};

#endif // __COLORS_HLSLI__