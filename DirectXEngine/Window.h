#pragma once
#include <Windows.h>

class Window
{
public:
	//Initialize the window
	Window(UINT width, UINT height);

	bool IsRun();

	RECT GetClientWindowRect();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	//Release the window
	~Window();

private:
	bool Broadcast();

protected:
	HWND m_hwnd;

	bool m_is_run;

	bool m_is_init = false;
};

