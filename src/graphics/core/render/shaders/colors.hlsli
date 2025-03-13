#ifndef __COLORS_HLSLI__
#define __COLORS_HLSLI__

#define MAX_COLORS 10

cbuffer colors : register(b0) {
    float4 color[MAX_COLORS];
    uint colorCount;
    float padding[3];
};

#endif // __COLORS_HLSLI__