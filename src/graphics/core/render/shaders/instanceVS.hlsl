#include "transform.hlsli"

// Structure des données de vertex
struct VS_IN {
    float4 position : POSITION; // Position du sommet dans le modèle
    float4x4 worldMatrix : InstanceTransform;
};

// Structure de sortie du vertex shader
struct VS_OUT {
    float4 position : SV_POSITION; // Position du sommet après transformation
};

VS_OUT main(VS_IN input, uint instanceID : SV_InstanceID) {
    
    VS_OUT output;

    // Récupérer la matrice de transformation de l'instance courante
    float4x4 worldMatrix = input.worldMatrix;

    // Appliquer la transformation du modèle à la position du sommet
    float4 worldPosition = mul(input.position, worldMatrix);
    float4 pos = mul(worldPosition, modelViewProjection);


    // Appliquer la matrice de projection et de vue si nécessaire
    output.position = pos;

    return output;
}