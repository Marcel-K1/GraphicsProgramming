/*********************************************************************************************
* Project: DirectXEngine
* File   : Material
* Date   : 18.02.2023
* Author : Marcel Klein
*
* Consists of constant buffer, vertex and pixel shaders and a texture for the pixel shader to evaluate.
*
*********************************************************************************************/

#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <vector>

//Handling for the material to show its front or back side polygons
enum CULL_MODE
{
	CULL_MODE_FRONT = 0,
	CULL_MODE_BACK
};

class GraphicsEngine;
class Material
{
public:
	Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);

	Material(const MaterialPtr& material);

	~Material();

	void AddTexture(const TexturePtr& texture);

	void RemoveTexture(unsigned int index);

	void SetData(void* data, unsigned int size);

	void SetCullMode(CULL_MODE mode);

	CULL_MODE GetCullMode();

private:
	VertexShaderPtr m_vertex_shader;

	PixelShaderPtr m_pixel_shader;

	ConstantBufferPtr m_constant_buffer;

	std::vector<TexturePtr> m_vec_textures;

	CULL_MODE m_cull_mode = CULL_MODE_BACK;

	friend class GraphicsEngine;
};

