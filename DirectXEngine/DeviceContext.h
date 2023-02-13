#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);

	void ClearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);

	void SetVertexBuffer(const VertexBufferPtr& vertex_buffer);

	void SetIndexBuffer(const IndexBufferPtr& index_buffer);



	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);

	void DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);


	void SetViewportSize(UINT width, UINT height);


	void SetVertexShader(const VertexShaderPtr& vertex_shader);

	void SetPixelShader(const PixelShaderPtr& pixel_shader);


	void SetTexture(const VertexShaderPtr& vertex_shader, const TexturePtr* texture, unsigned int num_textures);
		 
	void SetTexture(const PixelShaderPtr& pixel_shader, const TexturePtr* texture, unsigned int num_textures);


	void SetConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);

	void SetConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);


	~DeviceContext();

private:
	ID3D11DeviceContext* m_device_context;

	RenderSystem* m_system = nullptr;

private:
	friend class ConstantBuffer;

};
