#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include <exception>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

//Manager for the graphic system of the application, subdivided into RenderSystem and ResourceManager to allow the Single Responsability Principle.
//As Singleton to provide global access.
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

	//Compiling the data structure for the needed size of the created vertex mesh.
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


MaterialPtr GraphicsEngine::CreateMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	MaterialPtr mat = nullptr;
	try
	{
		mat = std::make_shared<Material>(vertex_shader_path, pixel_shader_path);
	}
	catch (...) {}
	return mat;
}

MaterialPtr GraphicsEngine::CreateMaterial(const MaterialPtr& material)
{
	MaterialPtr mat = nullptr;
	try
	{
		mat = std::make_shared<Material>(material);
	}
	catch (...) {}
	return mat;
}


void GraphicsEngine::SetMaterial(const MaterialPtr& material)
{
	//SET RASTERIZATION
	GraphicsEngine::Get()->GetRenderSystem()->SetRasterizerState((material->m_cull_mode == CULL_MODE_FRONT));

	//SET BUFFERS
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(material->m_vertex_shader, material->m_constant_buffer);
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(material->m_pixel_shader, material->m_constant_buffer);

	//SET SHADERS
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(material->m_vertex_shader);
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(material->m_pixel_shader);

	//SET TEXTURES
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(material->m_pixel_shader, &material->m_vec_textures[0], (UINT)material->m_vec_textures.size());
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