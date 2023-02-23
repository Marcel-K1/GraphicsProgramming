/*********************************************************************************************
* Project: DirectXEngine
* File   : SwapChain
* Date   : 10.01.2023
* Author : Marcel Klein
*
* Used to show the render frames on screen, by double buffering with front and back buffer.
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	//Initialize the SwapChain for a window.
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);

	void SetFullScreen(bool fullscreen, unsigned int width, unsigned int height);

	void Resize(unsigned int width, unsigned int height);

	bool Present(bool vsync);

	~SwapChain();

private:
	void ReloadBuffers(unsigned int width, unsigned int height);

private:
	IDXGISwapChain* m_swap_chain = nullptr;

	ID3D11RenderTargetView* m_rtv = nullptr;

	ID3D11DepthStencilView* m_dsv = nullptr;

	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};

