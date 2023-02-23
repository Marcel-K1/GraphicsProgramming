/*********************************************************************************************
* Project: DirectXEngine
* File   : EngineWindow
* Date   : 01.01.2023
* Author : Marcel Klein
*
* Class for handling the engines window and overall draw and mesh commands.
*
*********************************************************************************************/

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
	TexturePtr m_rough_tex;

	TexturePtr m_rough_normal_tex;

	TexturePtr m_ground_tex;

	TexturePtr m_matte_tex;

	TexturePtr m_glossy_tex;

	//Meshes
	MeshPtr m_mesh;

	MeshPtr m_sphere_mesh;

	MeshPtr m_plane_mesh;

	//Materials
	MaterialPtr m_mat;

	MaterialPtr m_matte_mat;

	MaterialPtr m_glossy_mat;

	MaterialPtr m_rough_mat;
	
	MaterialPtr m_ground_mat;


private:
	//Variables for time managment
	ULONGLONG m_old_delta;
	ULONGLONG m_new_delta;
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

