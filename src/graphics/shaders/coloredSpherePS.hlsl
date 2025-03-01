cbuffer colors : register(b0)
{
	float4 color[1];
};

float4 main() : SV_TARGET
{
	return color[0];
}