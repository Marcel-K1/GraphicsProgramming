#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"


class AppWindow : public Window, public InputListener
{
public:
	AppWindow(UINT width, UINT height);

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

public:
	void Render();

	void Update();

	void UpdateModel();

	void UpdateCamera();

	void UpdateSkyBox();
		 
	void DrawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, const PixelShaderPtr& ps, const ConstantBufferPtr& cb,
		const TexturePtr& tex);

private:
	SwapChainPtr m_swap_chain;

	VertexBufferPtr m_vb;

	VertexShaderPtr m_vs;

	PixelShaderPtr m_ps;

	PixelShaderPtr m_sky_ps;

	ConstantBufferPtr m_cb;

	ConstantBufferPtr m_sky_cb;

	IndexBufferPtr m_ib;

	TexturePtr m_wood_tex;

	TexturePtr m_sky_tex;

	MeshPtr m_mesh;

	MeshPtr m_sky_mesh;

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	//Variables for Input to change Rotation
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	//Variables for Light Settings
	float m_light_rot_y = 0.0f;

	//Variables for Input to change Scale
	float m_scale_cube = 1;

	//Variables for changing Camera Position
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	//Variables for Skybox Generation
	bool cull = true;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	//Window Management
	bool m_play_state = false;
	bool m_fullscreen_state = false;
};

