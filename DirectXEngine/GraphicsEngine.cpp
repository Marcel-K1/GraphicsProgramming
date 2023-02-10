//#include "GraphicsEngine.h"
//#include "SwapChain.h"
//#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

//As Singleton
GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("RenderSystem not created successfully"); }

	try
	{
		m_tex_manager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not created successfully"); }

	try
	{
		m_mesh_manager = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not created successfully"); }

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_system->CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "main", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->ReleaseCompiledShader();
}

RenderSystem* GraphicsEngine::GetRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::GetTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::GetMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;
}

void GraphicsEngine::Create()
{
	if (GraphicsEngine::m_engine) throw std::exception("GraphicsEngine already created");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::Release()
{
	if (!GraphicsEngine::m_engine) return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::Get()
{
	return m_engine;
}
