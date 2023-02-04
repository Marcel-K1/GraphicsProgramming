#pragma once
#include <d3d11.h>

#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class VertexShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);

	void ClearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

	void SetVertexBuffer(VertexBuffer* vertex_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);

	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(VertexShader* vertex_shader);

	bool Release();

	~DeviceContext();

private:
	ID3D11DeviceContext* m_device_context;
};
