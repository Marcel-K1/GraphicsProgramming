#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class RenderSystem
{
public:

	RenderSystem();

	//Initialize the GraphicsEngine and DirectX 11 Device
	bool Init();

	//Release all the resources loaded
	bool Release();

	~RenderSystem();

public:
	SwapChain* CreateSwapChain(HWND hwnd, UINT width, UINT height);

	DeviceContext* GetImmediateDeviceContext();

	VertexBuffer* CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	
	IndexBuffer* CreateIndexBuffer(void* list_indices, UINT size_list);
	
	ConstantBuffer* CreateConstantBuffer(void* buffer, UINT size_buffer);
	
	VertexShader* CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	
	PixelShader* CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);

public:
	bool CompileVertexShader(
		const wchar_t* file_name,
		const char* entry_point_name,
		void** shader_byte_code,
		size_t* byte_code_size);

	bool CompilePixelShader(
		const wchar_t* file_name,
		const char* entry_point_name,
		void** shader_byte_code,
		size_t* byte_code_size);

	void ReleaseCompiledShader();

	////DEFAULT SIMPLE SHADERS
	//bool CreateShaders();
	//bool SetShaders();

private:
	DeviceContext* m_imm_device_context;

private:
	ID3D11Device* m_d3d_device;

	D3D_FEATURE_LEVEL m_feature_level;

private:
	IDXGIDevice* m_dxgi_device;

	IDXGIAdapter* m_dxgi_adapter;

	IDXGIFactory* m_dxgi_factory;

	ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_blob = nullptr;

	ID3DBlob* m_vsblob = nullptr;

	ID3DBlob* m_psblob = nullptr;

	ID3D11VertexShader* m_vs = nullptr;

	ID3D11PixelShader* m_ps = nullptr;

private:
	friend class SwapChain;

	friend class VertexBuffer;

	friend class IndexBuffer;

	friend class ConstantBuffer;

	friend class VertexShader;

	friend class PixelShader;
};

