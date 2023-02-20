#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "Mesh.h"

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D m_camera_position;
	Vector4D m_light_position = Vector4D(0, 1, 0, 0);
	float m_light_radius = 4.0f;
	float m_time = 0.0f;
};

AppWindow::AppWindow(UINT width, UINT height) : Window(width, height)
{
}


void AppWindow::Render()
{
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);


	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW & SET CONSTANT BUFFER
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	//COMPUTE TRANSFORM MATRICES
	Update();

	//Rendering more than one Object
	for (int i = 0; i < 3; i++)
	{
		//RENDER MODEL
		UpdateModel(Vector3D(4.0f, 2.0f, -4.0f + 4.0f * i), m_wood_mat);
		DrawMesh(m_sky_mesh, m_wood_mat);

		//RENDER MODEL
		UpdateModel(Vector3D(0.0f, 2.0f, -4.0f + 4.0f * i), m_earth_mat);
		DrawMesh(m_sky_mesh, m_earth_mat);

		//RENDER MODEL
		UpdateModel(Vector3D(-4.0f, 2.0f, -4.0f + 4.0f * i), m_brick_mat);
		DrawMesh(m_sky_mesh, m_brick_mat);
	}

	//RENDER PLANE
	UpdateModel(Vector3D(0, 0, 0), m_mat);
	DrawMesh(m_plane_mesh, m_mat);

	//RENDER SKYBOX/SPHERE
	DrawMesh(m_sky_mesh, m_sky_mat);


	m_swap_chain->Present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
	m_time += m_delta_time;

}

void AppWindow::Update()
{
	UpdateCamera();
	UpdateLight();
	UpdateSkyBox();
}

void AppWindow::UpdateModel(Vector3D position, const MaterialPtr& material)
{
	constant cc;
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.SetIdentity();
	m_light_rot_matrix.SetRotationY(m_light_rot_y);
	cc.m_world.SetIdentity();
	cc.m_world.SetTranslation(position);
	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;
	cc.m_camera_position = m_world_cam.GetTranslation();
	cc.m_light_position = m_light_position;
	cc.m_light_radius = m_light_radius;
	cc.m_light_direction = m_light_rot_matrix.GetZDirection();
	cc.m_time = m_time;

	material->SetData(&cc, sizeof(constant));
}

void AppWindow::UpdateCamera()
{
	Matrix4x4 world_cam, temp;
	world_cam.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(m_rot_x);
	world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.GetTranslation() + world_cam.GetZDirection() * (m_forward * 0.05f);

	new_pos = new_pos + world_cam.GetXDirection() * (m_rightward * 0.05f);

	world_cam.SetTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.Inverse();

	m_view_cam = world_cam;

	int width = (this->GetClientWindowRect().right - this->GetClientWindowRect().left);
	int height = (this->GetClientWindowRect().bottom - this->GetClientWindowRect().top);

	m_proj_cam.SetPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
}

void AppWindow::UpdateSkyBox()
{
	constant cc;

	cc.m_world.SetIdentity();
	cc.m_world.SetScale(Vector3D(100.0f, 100.0f, 100.0f));
	cc.m_world.SetTranslation(m_world_cam.GetTranslation());
	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;

	m_sky_mat->SetData(&cc, sizeof(constant));
}

void AppWindow::UpdateLight()
{
	//Gives the light a slight rotation
	m_light_rot_y += 1.57f * m_delta_time;
	float dist_from_origin = 3.0f;
	m_light_position = Vector4D(cos(m_light_rot_y) * dist_from_origin, 2.0f, sin(m_light_rot_y) * dist_from_origin, 1.0f);
}

void AppWindow::DrawMesh(const MeshPtr& mesh, const MaterialPtr& material)
{
	GraphicsEngine::Get()->SetMaterial(material);

	//SET THE VERTICES OF THE TRIANGLES TO DRAW							   
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(mesh->GetVertexBuffer());

	//SET THE INDICES OF THE TRIANGLES TO DRAW 							   
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(mesh->GetIndexBuffer());
											  							   
	//DRAW THE TRIANGLES			  							   
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
}


AppWindow::~AppWindow()
{
}


void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::Get()->AddListener(this);

	m_play_state = true;
	InputSystem::Get()->ShowCursor(false);

	RECT rc = this->GetClientWindowRect();
	m_swap_chain = GraphicsEngine::Get()->GetRenderSystem()->CreateSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	//Texture Generation (Important to keep the paths correct! Otherwise nothing will be renderered.)
	m_brick_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick_d.jpg");
	m_brick_normal_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick_n.jpg");
	m_wall_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\wall.jpg");
	m_sky_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\stars_map.jpg");
	m_wood_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\wood.jpg");
	m_earth_tex = GraphicsEngine::Get()->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\earth_color.jpg");

	//Mesh Generation
	m_sky_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\sphere.obj");
	m_plane_mesh = GraphicsEngine::Get()->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\plane.obj");

	//Material Generation

	//With Matte Shader
	m_mat = GraphicsEngine::Get()->CreateMaterial(L"PointLightGlossyVertexShader.hlsl", L"PointLightGlossyPixelShader.hlsl");
	m_mat->AddTexture(m_wall_tex);
	m_mat->SetCullMode(CULL_MODE_BACK);

	m_earth_mat = GraphicsEngine::Get()->CreateMaterial(m_mat);
	m_earth_mat->AddTexture(m_earth_tex);
	m_earth_mat->SetCullMode(CULL_MODE_BACK);

	//With Glossy Shader
	m_wood_mat = GraphicsEngine::Get()->CreateMaterial(L"PointLightMatteVertexShader.hlsl", L"PointLightMattePixelShader.hlsl");
	m_wood_mat->AddTexture(m_wood_tex);
	m_wood_mat->SetCullMode(CULL_MODE_BACK);

	//With Rough Shader
	m_brick_mat = GraphicsEngine::Get()->CreateMaterial(L"PointLightRoughVertexShader.hlsl", L"PointLightRoughPixelShader.hlsl");
	m_brick_mat->AddTexture(m_brick_tex);
	m_brick_mat->AddTexture(m_brick_normal_tex);
	m_brick_mat->SetCullMode(CULL_MODE_BACK);	

	//Skybox Shader
	m_sky_mat = GraphicsEngine::Get()->CreateMaterial(L"PointLightMatteVertexShader.hlsl", L"SkyBoxShader.hlsl");
	m_sky_mat->AddTexture(m_sky_tex);
	m_sky_mat->SetCullMode(CULL_MODE_FRONT);

	m_world_cam.SetTranslation(Vector3D(0, 5, -10));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::Get()->Update();
	this->Render();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->SetFullScreen(false, 1, 1);
}


//Input Event Methods
void AppWindow::onFocus()
{
	InputSystem::Get()->AddListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::Get()->RemoveListener(this);
}

void AppWindow::onSize()
{
	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Resize(rc.right, rc.bottom);
	this->Render();
}

void AppWindow::onKeyDown(int key)
{
	if (!m_play_state) return;

	if (key == 'W')
	{
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
	}
	else if (key == 'O')
	{
		m_light_radius = (m_light_radius <= 0) ? 0.0f : m_light_radius - 1.0f * m_delta_time;
	}
	else if (key == 'P')
	{
		m_light_radius += 1.0f * m_delta_time;
	}
	else if (key == VK_ESCAPE)
	{
		m_is_run = false;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;

	if (key == 'G')
	{
		m_play_state = (m_play_state) ? false : true;
		InputSystem::Get()->ShowCursor(!m_play_state);
	}
	else if (key == 'F')
	{
		m_fullscreen_state = (m_fullscreen_state) ? false : true;
		RECT size_screen = this->GetSizeScreen();

		m_swap_chain->SetFullScreen(m_fullscreen_state, size_screen.right, size_screen.bottom);
	}
}

void AppWindow::onMouseMove(const Point & mouse_pos)
{
	if (!m_play_state) return;

	int width = (this->GetClientWindowRect().right - this->GetClientWindowRect().left);
	int height = (this->GetClientWindowRect().bottom - this->GetClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	InputSystem::Get()->SetCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

