struct VSOut {
    float2 texCoord : TexCoord;
    float4 position : SV_Position;
};

cbuffer TransformBuffer : register(b0) {
    matrix transform;
};

VSOut main(float3 position : Position, float2 texCoord : TexCoord) {
    VSOut output;
    output.position = mul(float4(position, 1.0f), transform);
    output.texCoord = texCoord;
    return output;
}