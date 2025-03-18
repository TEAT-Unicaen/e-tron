#ifndef __TRANSFORM_HLSLI__
#define __TRANSFORM_HLSLI__

cbuffer TransformBuffer : register(b0){
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

#endif // __TRANSFORM_HLSLI__