struct VSOut {
    float3 color : Color;
    float4 position : SV_POSITION;
};

VSOut main(float3 position : Position, float3 color : Color) {
    VSOut output;
    output.position = float4(position, 1.0f);
    output.color = color;
    return output;
}