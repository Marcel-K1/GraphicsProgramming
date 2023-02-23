/*********************************************************************************************
* Project: DirectXEngine
* File   : Window
* Date   : 01.01.2023
* Author : Marcel Klein
*
* Base Class for classes to inherit from in order to make them listeners follwing the observer-pattern
* like with the EngineWindow and be able to further develop the engine structure with more windows for
* example. Also setting up the basic structure for window creation and broadcasting.
*
*********************************************************************************************/

#pragma once
#include <Windows.h>

class Window
{
public:
	//Initialize the window
	Window(UINT width, UINT height);

	bool IsRun();

	RECT GetClientWindowRect();
	RECT GetSizeScreen();

	//Events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
	virtual void onSize();

	//Release the window
	~Window();

private:
	bool Broadcast();

protected:
	HWND m_hwnd;

	bool m_is_run;

	bool m_is_init = false;
};

