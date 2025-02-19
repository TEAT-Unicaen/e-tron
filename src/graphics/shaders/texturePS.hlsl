Texture2D texture0 : register(t0);

sampler sampler0 : register(s0);

struct PSOut {
	float4 color : SV_Target;
};

PSOut main(float2 texCoord : TexCoord) {
	PSOut output;
	output.color = texture0.Sample(sampler0, texCoord);
	return output;
}