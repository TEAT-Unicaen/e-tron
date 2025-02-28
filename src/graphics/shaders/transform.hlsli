#ifndef __TRANSFORM_HLSLI__
#define __TRANSFORM_HLSLI__

cbuffer Transform : register(b0){
    matrix transform;
};

#endif // __TRANSFORM_HLSLI__