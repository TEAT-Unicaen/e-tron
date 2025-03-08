#include "colors.hlsli"


float4 main(uint tid : SV_PrimitiveID) : SV_TARGET {
    if (tid % 8 == 0 || tid % 8 == 1) {
        return color[0]; // Haut
    } else if (tid % 8 == 2 || tid % 8 == 3) {
        return color[1]; // Bas
    } else {
        return color[2]; // Faces latérales
    }
}