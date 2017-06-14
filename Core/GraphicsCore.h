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

#pragma once

class CommandContext;
class CommandListManager;
class CommandSignature;
class ContextManager;
class ColorBuffer;
class DepthBuffer;
class SamplerDesc;

using D3D11_SAMPLER_HANDLE = ID3D11SamplerState*;

namespace Graphics
{
	using namespace Microsoft::WRL;

	extern uint32_t g_DisplayWidth;
	extern uint32_t g_DisplayHeight;

	// Returns the number of elapsed frames since application start
	uint64_t GetFrameCount(void);

	// The amount of time elapsed during the last completed frame.  The CPU and/or
	// GPU may be idle during parts of the frame.  The frame time measures the time
	// between calls to present each frame.
	float GetFrameTime(void);

	// The total number of frames per second
	float GetFrameRate(void);

	extern ColorBuffer g_DisplayPlane;
	extern ID3D11Device3* g_Device;
	extern CommandListManager g_CommandManager;
	extern ContextManager g_ContextManager;

	extern ID3D11DeviceContext3* g_Context;
	extern IDXGISwapChain1* s_SwapChain1;
	extern ID3D11RenderTargetView* g_RenderTargetView;

	extern SamplerDesc SamplerLinearWrapDesc;
	extern SamplerDesc SamplerAnisoWrapDesc;
	extern SamplerDesc SamplerShadowDesc;
	extern SamplerDesc SamplerLinearClampDesc;
	extern SamplerDesc SamplerVolumeWrapDesc;
	extern SamplerDesc SamplerPointClampDesc;
	extern SamplerDesc SamplerPointBorderDesc;
	extern SamplerDesc SamplerLinearBorderDesc;

	extern D3D11_SAMPLER_HANDLE SamplerLinearWrap;
	extern D3D11_SAMPLER_HANDLE SamplerAnisoWrap;
	extern D3D11_SAMPLER_HANDLE SamplerShadow;
	extern D3D11_SAMPLER_HANDLE SamplerLinearClamp;
	extern D3D11_SAMPLER_HANDLE SamplerVolumeWrap;
	extern D3D11_SAMPLER_HANDLE SamplerPointClamp;
	extern D3D11_SAMPLER_HANDLE SamplerPointBorder;
	extern D3D11_SAMPLER_HANDLE SamplerLinearBorder;

	extern D3D11_DEPTH_STENCIL_DESC DepthStateReadWrite;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateTestLess;
	extern D3D11_DEPTH_STENCIL_DESC DepthStateDisabled;
	
	extern D3D11_RASTERIZER_DESC RasterizerDefault;

	void Initialize( void );
	void Resize( uint32_t width, uint32_t height );
	void Terminate( void );
	void Shutdown( void );
	void Present( void );
}