/*********************************************************************************************
* Project: DirectXEngine
* File   : VertexBuffer
* Date   : 05.01.2023
* Author : Marcel Klein
*
* Works as memory buffer, that contains a list of vertices (but with only one layout,
* following the semantic structure below).
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader,
		RenderSystem * system);

	UINT GetSizeVertexList();

	~VertexBuffer();

private:
	UINT m_size_vertex;

	UINT m_size_list;

private:
	ID3D11Buffer* m_buffer;

	ID3D11InputLayout* m_layout;

	RenderSystem * m_system = nullptr;

private:
	friend class DeviceContext;
};

