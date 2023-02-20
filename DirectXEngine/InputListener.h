#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{
	}

	~InputListener()
	{
	}

	//KEYBOARD pure virtual callback functions 
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//MOUSE pure virtual callback functions
	virtual void onMouseMove(const Point& mouse_pos) = 0;
};
