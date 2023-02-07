#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

struct vertex
{
	Vector3D position;
	//Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

AppWindow::AppWindow()
{
}

void AppWindow::Update()
{
	constant cc;
	cc.m_time = ::GetTickCount64();
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;



	////For just changing Position of static quad
	// 
	//cc.m_world.SetTranslation(Vector3D(0, 0.5f, 0));



	////For just changing Scale of static quad
	// 
	//cc.m_world.SetScale(Vector3D(1.5f, 1.5f, 1.5f));



	////For changing Position and Scale dynamically over time
	// 
	//Matrix4x4 temp;
	// 
	//m_delta_scale += m_delta_time / 0.15f;
	//cc.m_world.SetScale(Vector3D::Lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.SetTranslation(Vector3D::Lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));
	////Multiplying the Scale Matrix with the Transformation Matrix 
	// (by using the overriden operator function in the header) to set up the World Matrix:
	//cc.m_world *= temp;



	////For changing Cube Rotation:
	// 
	//m_delta_pos += m_delta_time / 10.0f;
	//if (m_delta_pos > 1.0f)
	//	m_delta_pos = 0;

	//Matrix4x4 temp;

	//m_delta_scale += m_delta_time / 0.55f;

	//cc.m_world.SetScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

	//temp.SetIdentity();
	//temp.SetRotationZ(/*m_delta_scale*/0.0f);
	//cc.m_world *= temp;

	//temp.SetIdentity();
	//temp.SetRotationY(m_rot_y);
	//cc.m_world *= temp;

	//temp.SetIdentity();
	//temp.SetRotationX(m_rot_x);
	//cc.m_world *= temp;

	//cc.m_view.SetIdentity();
	//cc.m_proj.SetOrthoLH
	//(
	//	(this->GetClientWindowRect().right - this->GetClientWindowRect().left) / 300.0f,
	//	(this->GetClientWindowRect().bottom - this->GetClientWindowRect().top) / 300.0f,
	//	-4.0f,
	//	4.0f
	//);



	////For changing camera Position:
	// 
	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.55f;

	cc.m_world.SetIdentity();

	Matrix4x4 world_cam;
	world_cam.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(m_rot_x);
	world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.GetTranslation() + world_cam.GetZDirection()*(m_forward * 0.1f);

	new_pos = new_pos + world_cam.GetXDirection()*(m_rightward * 0.1f);

	world_cam.SetTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.Inverse();

	cc.m_view = world_cam;

	int width = (this->GetClientWindowRect().right - this->GetClientWindowRect().left);
	int height = (this->GetClientWindowRect().bottom - this->GetClientWindowRect().top);

	cc.m_proj.SetPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);



	m_cb->Update(GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::Get()->AddListener(this);

	InputSystem::Get()->ShowCursor(false);

	GraphicsEngine::Get()->Init();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain = GraphicsEngine::Get()->GetRenderSystem()->CreateSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//vertex list[] =
	//{
	//	//Quad: X - Y - Z
	//	{Vector3D(-0.5f,-0.5f,0.0f), Vector3D(-0.32f,-0.11f,0.0f), Vector3D(0,0,0), Vector3D(0,1,0) }, // POS1
	//	{Vector3D(-0.5f,0.5f,0.0f),  Vector3D(-0.11f,0.78f,0.0f),  Vector3D(1,1,0), Vector3D(0,1,1) }, // POS2
	//	{Vector3D(0.5f,-0.5f,0.0f),  Vector3D(0.75f,-0.73f,0.0f),  Vector3D(0,0,1), Vector3D(1,0,0) }, // POS2
	//	{Vector3D(0.5f,0.5f,0.0f),   Vector3D(0.88f,0.77f,0.0f),   Vector3D(1,1,1), Vector3D(0,0,1) }
	//};

	vertex vertex_list[] =
	{
		//Cube: X - Y - Z
		//FRONT FACE
		{ Vector3D(-0.5f,-0.5f,-0.5f), Vector3D(1,0,0), Vector3D(0.2f,0,0) },
		{ Vector3D(-0.5f,0.5f,-0.5f),  Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),  Vector3D(1,0,0), Vector3D(0.2f,0,0) },
		
		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),  Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),   Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),  Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f), Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};

	//UINT size_list = ARRAYSIZE(list);
	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,		//FIRST TRIANGLE
		2,3,0,		//SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::Get()->GetRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	GraphicsEngine::Get()->GetRenderSystem()->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

	//Pixel Shader
	GraphicsEngine::Get()->GetRenderSystem()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::Get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);

	GraphicsEngine::Get()->GetRenderSystem()->ReleaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::Get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::Get()->Update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW & SET CONSTANT BUFFER
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	Update();

	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	//SET VERTEX- & PIXEL-SHADERS IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::Get()->SetShaders();
	//GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(m_ib);

	////DRAW THE TRIANGLE WITH TRIANGLE STRIP
	//GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetSizeVertexList(), 0);
	//DRAW THE TRIANGLE WITH INDEXED TRIANGLE LIST
	GraphicsEngine::Get()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
	m_swap_chain->Present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::Get()->Release();
}

//Input Event Methods

//Handling the Window Focus
void AppWindow::onFocus()
{
	InputSystem::Get()->AddListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::Get()->RemoveListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		/*m_rot_x += 3.14f * m_delta_time;*/
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		/*m_rot_x -= 3.14f * m_delta_time;*/
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_rightward = 1.0f;
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
}

void AppWindow::onMouseMove(const Point & mouse_pos)
{
	//m_rot_x += delta_mouse_pos.m_y * m_delta_time * 0.01f;
	//m_rot_y += delta_mouse_pos.m_x * m_delta_time * 0.01f;

	int width = (this->GetClientWindowRect().right - this->GetClientWindowRect().left);
	int height = (this->GetClientWindowRect().bottom - this->GetClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	InputSystem::Get()->SetCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}
