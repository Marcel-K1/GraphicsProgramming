/*********************************************************************************************
* Project: DirectXEngine
* File   : main
* Date   : 01.01.2023
* Author : Marcel Klein
*
* Class for setting up the applications main loop.
*
*********************************************************************************************/

#include "EngineWindow.h"
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
			EngineWindow app(1024, 768);
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