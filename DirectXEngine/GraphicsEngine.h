#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

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

public:
	static GraphicsEngine* Get();

	static void Create();

	static void Release();

private:
	RenderSystem* m_render_system = nullptr;

	static GraphicsEngine* m_engine;
};
