cbuffer colors : register(b0)
{
    float4 color[3]; // 0 = haut, 1 = bas, 2 = latéral
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET // /!\ ON SUPPOSE 20 
{
    if (tid % 4 == 2)
    { // Supposons 20 triangles pour le haut
        return color[0]; // Haut
    }
    else if (tid % 4 == 3)
    { // Supposons 20 triangles pour le bas
        return color[1]; // Bas
    }
    else
    {
        return color[2]; // Faces latérales
    }
}
