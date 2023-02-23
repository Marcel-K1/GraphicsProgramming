/*********************************************************************************************
* Project: DirectXEngine
* File   : ConstantBuffer
* Date   : 01.02.2023
* Author : Marcel Klein
*
* Works as memory buffer, which allows to put in any data you want, and then pass it to any shader.
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system);

	void Update(DeviceContextPtr context, void* buffer);

	~ConstantBuffer();

private:
	ID3D11Buffer* m_buffer;

	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

