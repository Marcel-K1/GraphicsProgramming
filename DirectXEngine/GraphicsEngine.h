#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"

//As Singleton
class GraphicsEngine
{
private:
	//Initialize the GraphicsEngine and DirectX 11 Device
	GraphicsEngine();

	//Release all the resources loaded
	~GraphicsEngine();

public:
	RenderSystem* GetRenderSystem();

	TextureManager* GetTextureManager();

	MeshManager* GetMeshManager();

	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

public:
	static GraphicsEngine* Get();

	static void Create();

	static void Release();

private:
	RenderSystem* m_render_system = nullptr;

	TextureManager* m_tex_manager = nullptr;

	MeshManager* m_mesh_manager = nullptr;

	static GraphicsEngine* m_engine;

	unsigned char m_mesh_layout_byte_code[1024];

	size_t m_mesh_layout_size = 0;
};
