#include "AppWindow.h"

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
	swapChain = GraphicsEngine::Get()->CreateSwapChain();
	RECT rc = this->GetClientWindowRect();
	swapChain->Init(this->hwnd, rc.right - rc.left, rc.bottom - rc.top);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	swapChain->Release();
	GraphicsEngine::Get()->Release();
}
