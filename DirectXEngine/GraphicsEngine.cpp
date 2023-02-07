#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
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
	catch (...) { throw std::exception("GraphicsEngine not created successfully"); }
}

RenderSystem* GraphicsEngine::GetRenderSystem()
{
	return m_render_system;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
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
