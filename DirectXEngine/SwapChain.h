#pragma once
#include <d3d11.h>

class SwapChain
{

public:
	SwapChain();

	//Initialize SwapChain for a window
	bool Init(HWND hwnd, UINT width, UINT height);

	//Release the swap chain
	bool Release();

	~SwapChain();

private:
	IDXGISwapChain* swapChain;

};

