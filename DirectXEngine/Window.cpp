#include "Window.h"

Window::Window()
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//Event fired when the window is created
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->SetHWND(hwnd);
		window->onCreate();
		break;
	}
	case WM_SETFOCUS:
	{
		//Event fired when the window get focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		//Event fired when the window lost focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}
	case WM_DESTROY:
	{
		//Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}


	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::Init(UINT width, UINT height)
{
	//Setting up WNDCLASSEX object
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass",
	wc.lpszMenuName = L"DirectX Engine",
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT windowRect = {
		(screenWidth - width) / 2,
		(screenHeight - height) / 2,
		(screenWidth + width) / 2,
		(screenHeight + height) / 2
	};

	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	//If the registration of class will fail, the function will return false
	if (!::RegisterClassEx(&wc))
		return false;

	//Creation of the window
	m_hwnd = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"MyWindowClass",
		L"DirectX Engine",
		WS_OVERLAPPEDWINDOW,
		windowRect.left, windowRect.top,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		NULL, NULL, NULL, this);

	//If the creation fail return false
	if (!m_hwnd)
		return false;

	//Show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	//Set this flag to true to indicate that the window is initialized and running
	m_is_run = true;

	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

bool Window::Release()
{
	//Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::IsRun()
{
	return m_is_run;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

Window::~Window()
{
}
