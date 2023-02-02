#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

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
	SwapChain* CreateSwapChain();

public:
	static GraphicsEngine* Get();

private:
	ID3D11Device* d3dDevice;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11DeviceContext* immContext;

private:
	IDXGIDevice* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory* dxgiFactory;

private:
	friend class SwapChain;

};

