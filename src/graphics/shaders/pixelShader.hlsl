
cbuffer colors : register(b0) {
    float3 color[6];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
	return float4(color[tid/2], 1.0f);
}