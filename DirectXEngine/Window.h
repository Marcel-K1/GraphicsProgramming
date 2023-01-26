#pragma once
#include <Windows.h>


class Window
{

public:
	Window();

	//Initialize the window
	bool Init(UINT width, UINT height);

	bool Broadcast();

	//Release the window
	bool Release();

	bool IsRun();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();

private:
	HWND m_hwnd;
	bool m_is_run;
};

