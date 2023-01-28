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
	static GraphicsEngine* Get();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

};

