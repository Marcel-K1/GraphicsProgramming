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

	RECT GetClientWindowRect();
	void SetHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();

protected:
	HWND hwnd;
	bool isRun;
};

