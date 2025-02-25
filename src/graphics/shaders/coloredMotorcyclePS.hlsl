
cbuffer colors : register(b0) {
    float4 color[9];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
    if (tid < 4)
        return color[tid];
    return color[((tid+4) / 2 )];
}