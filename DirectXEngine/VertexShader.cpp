#include "VertexShader.h"
#include "GraphicsEngine.h"


VertexShader::VertexShader()
{
}

bool VertexShader::Init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::Get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		return false;

	return true;
}

void VertexShader::Release()
{
	m_vs->Release();
	delete this;
}

VertexShader::~VertexShader()
{
}
