/*********************************************************************************************
* Project: DirectXEngine
* File   : VertexShader
* Date   : 05.01.2023
* Author : Marcel Klein
*
* Gets the hlsl code to be then compiled by the render system.
*
* * Reference to: https://www.youtube.com/watch?v=luuyjjOxnUI&list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3
* https://www.youtube.com/watch?v=hRL56gXqj-4&list=PLU2nPsAdxKWQYxkmQ3TdbLsyc1l2j25XM
* https://www.youtube.com/watch?v=gQIG77PfLgo&list=PLcacUGyBsOIBlGyQQWzp6D1Xn6ZENx9Y2
*********************************************************************************************/

#include "VertexShader.h"
#include "RenderSystem.h"
#include <exception>

VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system) : m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		throw std::exception("VertexShader not created successfully");
}

VertexShader::~VertexShader()
{
	m_vs->Release();
}
