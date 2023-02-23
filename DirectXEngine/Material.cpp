/*********************************************************************************************
* Project: DirectXEngine
* File   : Material
* Date   : 18.02.2023
* Author : Marcel Klein
*
* Consists of constant buffer, vertex and pixel shaders and a texture for the pixel shader to evaluate.
*
* * Reference to: https://www.youtube.com/watch?v=luuyjjOxnUI&list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3
* https://www.youtube.com/watch?v=hRL56gXqj-4&list=PLU2nPsAdxKWQYxkmQ3TdbLsyc1l2j25XM
* https://www.youtube.com/watch?v=gQIG77PfLgo&list=PLcacUGyBsOIBlGyQQWzp6D1Xn6ZENx9Y2
*********************************************************************************************/

#include "Material.h"
#include "GraphicsEngine.h"
#include <exception>
#include <stdexcept>

Material::Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::Get()->GetRenderSystem()->CompileVertexShader(vertex_shader_path, "main", &shader_byte_code, &size_shader);
	m_vertex_shader = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

	if (!m_vertex_shader) throw std::runtime_error("Material not created successfully");

	GraphicsEngine::Get()->GetRenderSystem()->CompilePixelShader(pixel_shader_path, "main", &shader_byte_code, &size_shader);
	m_pixel_shader = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

	if (!m_pixel_shader) throw std::runtime_error("Material not created successfully");

}

Material::Material(const MaterialPtr& material)
{
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

Material::~Material()
{
}

//Using dynamic array with sharedPtr to manage multiple textures
void Material::AddTexture(const TexturePtr& texture)
{
	m_vec_textures.push_back(texture);
}

void Material::RemoveTexture(unsigned int index)
{
	if (index >= this->m_vec_textures.size()) return;
	m_vec_textures.erase(m_vec_textures.begin() + index);
}

void Material::SetData(void* data, unsigned int size)
{
	if (!m_constant_buffer)
		m_constant_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(data, size);
	else
		m_constant_buffer->Update(GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext(), data);
}

void Material::SetCullMode(CULL_MODE mode)
{
	m_cull_mode = mode;
}

CULL_MODE Material::GetCullMode()
{
	return m_cull_mode;
}
