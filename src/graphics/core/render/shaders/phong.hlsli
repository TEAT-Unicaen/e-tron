#ifndef __PHONG_HLSL__
#define __PHONG_HLSL__

// DATA
struct LightBuffer {
    float3 lightPosition;
    float3 lightColor;
    float3 ambient;
    float diffuseIntensity;
    float attConst;
    float attLinear;
    float attQuad;
};
StructuredBuffer<LightBuffer> lightBuffers : register(t1);


struct ToL {
    float3 vec;
    float dist;
    float3 dir;
};

// FUNCTIONS
ToL toLight(float3 lightPos, float3 viewPos) {
    ToL toL;
    toL.vec = lightPos - viewPos;
    toL.dist = length(toL.vec);
    toL.dir = toL.vec / toL.dist;
    return toL;
}

float attenuate(float attConst, float attLinear, float attQuad, float distToL) {
    return 1.0f / (attConst + attLinear * distToL + attQuad * (distToL * distToL));
}

float3 diffuse(float3 lightColor, float diffuseIntensity, float att, float3 dirToL, float3 viewNormal) {
    return lightColor * diffuseIntensity * att * max(0.0f, dot(dirToL, viewNormal));
}

float4 saturateColor(float3 diffuse, float3 ambiant, float4 color) {
    return float4(saturate(diffuse + ambiant), 1.0f) * color;
}





#endif // __PHONG_HLSL__