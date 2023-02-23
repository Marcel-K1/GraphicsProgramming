/*********************************************************************************************
* Project: DirectXEngine
* File   : Texture
* Date   : 05.02.2023
* Author : Marcel Klein
*
* Class for handling and computing the texture data imported by file using the DirectXTex Library
* and setting up the resource view and sampler description.
*
* Reference to: https://github.com/microsoft/DirectXTex
*********************************************************************************************/

#pragma once
#include "Prerequisites.h"
#include "Resource.h"

#include <d3d11.h>

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path);

	~Texture();

private:
	ID3D11Resource* m_texture = nullptr;

	ID3D11ShaderResourceView *m_shader_res_view = nullptr;

	ID3D11SamplerState* m_sampler_state = nullptr;

private:
	friend class DeviceContext;

};

