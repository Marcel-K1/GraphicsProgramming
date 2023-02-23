/*********************************************************************************************
* Project: DirectXEngine
* File   : PixelShader
* Date   : 05.01.2023
* Author : Marcel Klein
*
* Gets the hlsl code to be then compiled by the render system.
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);

	~PixelShader();

private:
	ID3D11PixelShader* m_ps;

	RenderSystem* m_system = nullptr;

private:
	friend class RenderSystem;

	friend class DeviceContext;
};

