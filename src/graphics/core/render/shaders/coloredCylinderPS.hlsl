cbuffer colors : register(b0)
{
    float4 color[3]; // 0 = haut, 1 = bas, 2 = latéral
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
    if (tid % 4 == 2)
    { 
        return color[0]; // Haut
    }
    else if (tid % 4 == 3)
    { 
        return color[1]; // Bas
    }
    else
    {
        return color[2]; // Faces latérales
    }
}
