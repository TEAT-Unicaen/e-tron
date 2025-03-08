Texture2D texture0 : register(t0);

sampler sampler0 : register(s0);

float4 main(float2 texCoord : TexCoord) : SV_Target {
    return texture0.Sample(sampler0, texCoord);
}