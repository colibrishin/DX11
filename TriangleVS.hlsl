
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
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

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    float3 scaledPos = _in.vPos;
    scaledPos.x *= cbScale.x;
    scaledPos.y *= cbScale.y;
    scaledPos.z *= cbScale.z;

    output.vPos = float4(scaledPos + cbPos.xyz, 1.f);
    output.vPos = mul(output.vPos, worldMatrix);
    output.vPos = mul(output.vPos, viewMatrix);
    output.vPos = mul(output.vPos, projectionMatrix);

    output.vColor = _in.vColor;
    
    return output;
}
