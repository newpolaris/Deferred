struct PixelShaderInput
{
	float4 posH : SV_POSITION;
    float4 shadowPosH : POSITION0;
};

cbuffer PassConstants : register(b1)
{
    float3 SunDirection;
    float3 SunColor;
    float4 ShadowTexelSize;
}

Texture2D<float>	texShadow        : register(t0);
SamplerComparisonState samplerShadow : register(s2);

#include "Shadow.hlsli"

float4 main(PixelShaderInput input) : SV_TARGET
{
    ShadowTex tex = { ShadowTexelSize, input.posH.xyz, 0 };
	float shadow = GetShadow(tex, input.shadowPosH);
    return float4(shadow.xxx, 1.0f);
}