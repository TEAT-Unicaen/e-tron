#include "../../transform.hlsli"

struct VS_IN {
    float3 position : Position; // Position du sommet dans le modèle
    float3 normal : Normal; // Normale du sommet dans le modèle
    float4x4 worldMatrix : InstanceTransform;
    float4 color : Color;
};

struct VSOut {
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    float4 color : Color;
    float4 position : SV_Position;
};

VSOut main(VS_IN input) {
    VSOut output;

    float4 pos4 = float4(input.position, 1.0f);

    float4x4 realModel = mul(input.worldMatrix, model);
    
    output.viewPos = mul(pos4, realModel).xyz;

    output.viewNormal = normalize(mul(input.normal, (float3x3)realModel));
    
    output.color = input.color;

    float4 worldPosition = mul(pos4, realModel);
    output.position = mul(worldPosition, mul(view, projection));

    return output;
}
