#include "../../transform.hlsli"

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
    float4x4 modelViewProjection = mul(model, mul(view, projection));
    VSOut output;

    float4 pos4 = float4(input.position, 1.0f);

    // Transformation de la position
    float4 worldPosition = mul(pos4, input.worldMatrix);
    output.viewPos = mul(worldPosition, model).xyz;

    // Transformation correcte de la normal
    float3x3 normalMatrix = (float3x3)mul(input.worldMatrix, model);
    output.viewNormal = normalize(mul(input.normal, normalMatrix));

    // Application de la transformation complète
    output.position = mul(worldPosition, modelViewProjection);

    return output;
}
