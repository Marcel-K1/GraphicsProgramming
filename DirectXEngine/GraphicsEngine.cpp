#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"

#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::Init()
{
	m_render_system = new RenderSystem();
	m_render_system->Init();
	return true;
}

bool GraphicsEngine::Release()
{
	m_render_system->Release();
	delete m_render_system;
	return true;
}

RenderSystem* GraphicsEngine::GetRenderSystem()
{
	return m_render_system;
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
