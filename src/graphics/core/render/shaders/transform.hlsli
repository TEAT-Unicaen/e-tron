#ifndef __TRANSFORM_HLSLI__
#define __TRANSFORM_HLSLI__

cbuffer TransformBuffer : register(b0){
    float4x4 model;
    float4x4 modelView;
    float4x4 modelViewProjection;
};

#endif // __TRANSFORM_HLSLI__