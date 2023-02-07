#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:

	GraphicsEngine();

	//Initialize the GraphicsEngine and DirectX 11 Device
	bool Init();

	//Release all the resources loaded
	bool Release();

	~GraphicsEngine();

public:
	RenderSystem* GetRenderSystem();

public:
	static GraphicsEngine* Get();

private:
	RenderSystem* m_render_system = nullptr;
};
