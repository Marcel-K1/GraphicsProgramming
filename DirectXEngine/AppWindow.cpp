#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::Get()->Init();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f}, // POS1
		{-0.5f,0.5f,0.0f}, // POS2
		{ 0.5f,-0.5f,0.0f },// POS2
		{ 0.5f,0.5f,0.0f}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::Get()->CreateShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::Get()->ReleaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::Get()->SetShaders();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetSizeVertexList(), 0);
	m_swap_chain->Present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->Release();
	m_swap_chain->Release();
	GraphicsEngine::Get()->Release();
}
