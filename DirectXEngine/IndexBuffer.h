/*********************************************************************************************
* Project: DirectXEngine
* File   : IndexBuffer
* Date   : 20.01.2023
* Author : Marcel Klein
*
* Memory Buffer, that contains a list of indices, for the mesh to be build correctly using DrawINDEXEDTriangleList.
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list, RenderSystem* system);

	UINT GetSizeIndexList();

	~IndexBuffer();

private:
	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;

	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

