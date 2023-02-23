/*********************************************************************************************
* Project: DirectXEngine
* File   : IndexBuffer
* Date   : 20.01.2023
* Author : Marcel Klein
*
* Memory Buffer, that contains a list of indices, for the mesh to be build correctly using DrawINDEXEDTriangleList.
*
* * Reference to: https://www.youtube.com/watch?v=luuyjjOxnUI&list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3
* https://www.youtube.com/watch?v=hRL56gXqj-4&list=PLU2nPsAdxKWQYxkmQ3TdbLsyc1l2j25XM
* https://www.youtube.com/watch?v=gQIG77PfLgo&list=PLcacUGyBsOIBlGyQQWzp6D1Xn6ZENx9Y2
*********************************************************************************************/

#include "IndexBuffer.h"
#include "RenderSystem.h"
#include <exception>

IndexBuffer::IndexBuffer(void* list_indices, UINT size_list, RenderSystem* system) : m_system(system), m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("IndexBuffer not created successfully");
	}
}

UINT IndexBuffer::GetSizeIndexList()
{
	return this->m_size_list;
}

IndexBuffer::~IndexBuffer()
{
	m_buffer->Release();
}
