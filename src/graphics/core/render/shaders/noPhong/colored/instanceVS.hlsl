#include "../../transform.hlsli"

// Structure des donn�es de vertex
struct VS_IN {
    float4 position : POSITION; // Position du sommet dans le mod�le
    float4x4 worldMatrix : InstanceTransform;
};

// Structure de sortie du vertex shader

float4 main(VS_IN input, uint instanceID : SV_InstanceID) : SV_POSITION {
    
    float4x4 modelViewProjection = mul(model, mul(view, projection));
   
    float4 worldPosition = mul(input.position, input.worldMatrix);

    // Appliquer la matrice de projection et de vue si n�cessaire
    return mul(worldPosition, modelViewProjection);;
}