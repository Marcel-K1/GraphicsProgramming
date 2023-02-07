#include "AppWindow.h"
#include "InputSystem.h"

int main()
{
	try
	{
		GraphicsEngine::Create();
		InputSystem::Create();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow app(1024, 768);
			while (app.IsRun());
		}
		catch (...) {
			InputSystem::Release();
			GraphicsEngine::Release();
			return -1;
		}
	}

	InputSystem::Release();
	GraphicsEngine::Release();

	return 0;
}