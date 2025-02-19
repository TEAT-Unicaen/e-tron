cbuffer Transform : register(b0) {
    matrix transform;
};

struct VSOut {
    float4 position : SV_POSITION;
};

VSOut main(float3 position : Position)
{
    VSOut output;
    output.position = mul(float4(position, 1.0f), transform);
    return output;
}