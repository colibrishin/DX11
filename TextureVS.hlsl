//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
};

cbuffer TRANSFORM : register(b0)
{
    float4 cbPos;
    float4 cbRot;
    float4 cbScale;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType TextureVertexShader(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    float3 scaledPos = input.position;
    scaledPos.x *= cbScale.x;
    scaledPos.y *= cbScale.y;
    scaledPos.z *= cbScale.z;

    output.position = float4(scaledPos + cbPos.xyz, 1.f);

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    return output;
}
