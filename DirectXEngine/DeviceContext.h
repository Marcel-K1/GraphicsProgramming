#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);

	void ClearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);

	void SetVertexBuffer(VertexBufferPtr vertex_buffer);

	void SetIndexBuffer(IndexBufferPtr index_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);

	void DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(VertexShaderPtr vertex_shader);

	void SetPixelShader(PixelShaderPtr pixel_shader);

	void SetConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);

	void SetConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);

	~DeviceContext();

private:
	ID3D11DeviceContext* m_device_context;

	RenderSystem* m_system = nullptr;

private:
	friend class ConstantBuffer;

};
