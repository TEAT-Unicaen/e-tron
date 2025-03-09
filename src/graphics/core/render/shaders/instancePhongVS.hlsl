#include "transform.hlsli"

struct VS_IN
{
    float3 position : POSITION; // Position du sommet dans le modèle
    float3 normal : NORMAL; // Normale du sommet dans le modèle
    float4x4 worldMatrix : InstanceTransform;
};


struct VSOut
{
    float3 viewPos : Position;
    float3 viewNormal : Normal;
    float4 position : SV_Position;
};


VSOut main(VS_IN input) {
    
    float4 pos4 = float4(input.position, 1.0f);

    VSOut output;
    output.viewPos = mul(mul(pos4, model), input.worldMatrix).xyz;
    output.viewNormal = normalize(mul(input.normal, (float3x3) model));
    
    float4x4 worldMatrix = input.worldMatrix;
    // Appliquer la transformation du modèle à la position du sommet
    float4 worldPosition = mul(pos4, worldMatrix);
    float4 pos = mul(worldPosition, modelViewProjection);
    // Appliquer la matrice de projection et de vue si nécessaire
    output.position = pos;
    
    return output;
}
