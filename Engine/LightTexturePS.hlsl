//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

cbuffer LightBuffer : register(b3)
{
	float4 diffuseColor;
	float3 lightDirection;
	float lightIntensity;
	float _padding;
}

////////////////////////////////////////////////////////////////////////////////
// Filename: texture.ps
////////////////////////////////////////////////////////////////////////////////

/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TexturePixelShader(PixelInputType input) : SV_TARGET
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	const float4 textureColor = shaderTexture.Sample(SampleType, input.tex);

	const float3 lightDir = -lightDirection;
	const float lightIntensity = saturate(dot(input.normal, lightDir));

	float4 color = saturate(diffuseColor * lightIntensity);
	color = color * textureColor;

	return color;
}
