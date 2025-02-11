

struct GS_INPUT {
    float4 color : Color;
    float4 position : POSITION; // Position du sommet
};

struct GS_OUTPUT {
    float4 position : SV_POSITION;
};

cbuffer gridValues : register(b0) {
    uint nbLines;
    uint nbColumns;
    uint nbVertex;
};

[maxvertexcount(255)]
void main(line GS_INPUT input[2], inout LineStream<GS_OUTPUT> output)
{
    GS_OUTPUT vertex[255];
    float lineOffset = 1.0f / (float) nbLines;
    float columnOffset = 1.0f / (float) nbColumns;
    for (int i = 0; i < nbLines; i++) {
        vertex[2 * i].position = float4(input[0].position.x, input[0].position.y + lineOffset, input[0].position.z, input[0].position.w);
        output.Append(vertex[2 * i]);
    }
    for (int j = 0; j < nbColumns; j++) {
        vertex[2 * j + nbLines].position = float4(input[0].position.x + columnOffset, input[0].position.y, input[0].position.z, input[0].position.w);
        output.Append(vertex[2 * j + nbLines]);
    }
}