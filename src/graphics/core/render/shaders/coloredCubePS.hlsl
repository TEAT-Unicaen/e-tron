cbuffer colors : register(b0) {
    float4 color[10];
    uint colorCount;
    float padding[3];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
    return color[(tid / 2) % colorCount];
}