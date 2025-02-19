
cbuffer colors : register(b0) {
    float4 color[5];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
    if (tid < 2)
        return color[0];
    return color[(tid-1)];
}