/*********************************************************************************************
* Project: DirectXEngine
* File   : InputListener
* Date   : 15.01.2023
* Author : Marcel Klein
*
* Base Class for classes to inherit from in order to make them listeners follwing the observer-pattern
* like with the EngineWindow and be able to further develop the engine structure.
*
*********************************************************************************************/

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

	//KEYBOARD virtual functions 
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//MOUSE virtual functions
	virtual void onMouseMove(const Point& mouse_pos) = 0;
};
