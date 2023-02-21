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


class EngineWindow : public Window, public InputListener
{
public:
	EngineWindow(UINT width, UINT height);

	~EngineWindow();

	// Inherited via window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

	// Inherited via inputlistener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

public:
	void Render();

	void Update();

	void UpdateModel(Vector3D position, const MaterialPtr& material);

	void UpdateCamera();

	void UpdateSkyBox();

	void UpdateLight();
		 
	void DrawMesh(const MeshPtr& mesh, const MaterialPtr& material);

private:
	//Shared Pointers
	SwapChainPtr m_swap_chain;

	VertexBufferPtr m_vb;

	VertexShaderPtr m_vs;

	PixelShaderPtr m_ps;

	PixelShaderPtr m_sky_ps;

	ConstantBufferPtr m_cb;

	ConstantBufferPtr m_sky_cb;

	IndexBufferPtr m_ib;

	//Textures
	TexturePtr m_brick_tex;

	TexturePtr m_brick_normal_tex;

	TexturePtr m_wall_tex;

	TexturePtr m_sky_tex;

	TexturePtr m_earth_tex;

	TexturePtr m_wood_tex;

	//Meshes
	MeshPtr m_mesh;

	MeshPtr m_sky_mesh;

	MeshPtr m_torus_mesh;

	MeshPtr m_suzanne_mesh;

	MeshPtr m_plane_mesh;

	MeshPtr m_box_mesh;

	//Materials
	MaterialPtr m_mat;

	MaterialPtr m_wood_mat;

	MaterialPtr m_earth_mat;

	MaterialPtr m_brick_mat;
	
	MaterialPtr m_wall_mat;

	MaterialPtr m_sky_mat;

private:
	//Variables for time managment
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	//Variables for input to change rotation
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	//Variables for light settings
	float m_light_rot_y = 0.0f;

	//Variables for changing camera position
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	//Variables for skybox
	bool cull = true;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	//Variables for Point Light
	float m_time = 0.0f;
	float m_light_radius = 4.0f;
	float m_attenuation = 2.0f;
	Vector4D m_light_position;

	//Window Management
	bool m_play_state = false;
	bool m_fullscreen_state = false;
};

