//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL;
};

cbuffer MatrixBuffer : register(b1)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer TRANSFORM : register(b2)
{
    float4 cbPos;
    float4 cbRot;
    float4 cbScale;
};

// TODO: rotation https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724

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

    const float3 up = cbRot;
    float3 forward = float3(0, 0, 1);
    const float3 right = normalize(cross(up, forward));
    forward = cross(right, up);

    const float3x3 rotationMatrix = float3x3(right, up, forward);
    scaledPos = mul(scaledPos, rotationMatrix);

    output.position = float4(scaledPos + cbPos.xyz, 1.f);

    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.normal = mul(input.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);

    

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    return output;
}
