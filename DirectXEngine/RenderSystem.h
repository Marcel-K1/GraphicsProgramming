/*********************************************************************************************
* Project: DirectXEngine
* File   : RenderSystem
* Date   : 15.02.2023
* Author : Marcel Klein
*
* Initializes the GraphicsEngine and DirectX 11 Device/API. By using sharedPtr,
* we shorthen the code base and make them more accessible.
*
*********************************************************************************************/

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class RenderSystem
{
public:

	//Initialize the GraphicsEngine and DirectX 11 Device/API
	RenderSystem();

	//Release all the resources loaded
	~RenderSystem();

public:
	SwapChainPtr CreateSwapChain(HWND hwnd, UINT width, UINT height);

	DeviceContextPtr GetImmediateDeviceContext();

	VertexBufferPtr CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	
	IndexBufferPtr CreateIndexBuffer(void* list_indices, UINT size_list);
	
	ConstantBufferPtr CreateConstantBuffer(void* buffer, UINT size_buffer);
	
	VertexShaderPtr CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	
	PixelShaderPtr CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);

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

	void SetRasterizerState(bool cull_front);

private:
	void InitRasterizerState();

private:
	DeviceContextPtr m_imm_device_context;

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

	ID3D11RasterizerState* m_cull_front_state = nullptr;
	ID3D11RasterizerState* m_cull_back_state = nullptr;

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

	friend class Texture;

};

