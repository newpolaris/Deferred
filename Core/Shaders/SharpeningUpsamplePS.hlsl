//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#include "ShaderUtility.hlsli"

Texture2D<float3> ColorTex : register(t0);
SamplerState BilinearClamp : register(s0);

cbuffer Constants : register(b0)
{
	float2 UVOffset0;
	float2 UVOffset1;
	float WA, WB;
}

float3 GetColor(float2 UV)
{
	float3 Color = ColorTex.SampleLevel(BilinearClamp, UV, 0);
#ifdef GAMMA_SPACE
	return ApplyDisplayProfile(Color, DISPLAY_PLANE_FORMAT);
#else
	return Color;
#endif
}

float3 main(float4 position : SV_Position, float2 uv : TexCoords0) : SV_Target0
{
    //
    // Sharpening Kernel
    //
	float3 Color = WB * GetColor(uv) - WA * (
		GetColor(uv + UVOffset0) + GetColor(uv - UVOffset0) +
		GetColor(uv + UVOffset1) + GetColor(uv - UVOffset1));

#ifdef GAMMA_SPACE
	return Color;
#else
	return ApplyDisplayProfile(Color, DISPLAY_PLANE_FORMAT);
#endif
}
