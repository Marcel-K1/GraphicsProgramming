#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	//Initialize SwapChain for a window
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);

	bool Present(bool vsync);

	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain = nullptr;

	ID3D11RenderTargetView* m_rtv = nullptr;

	ID3D11DepthStencilView* m_dsv = nullptr;

	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

