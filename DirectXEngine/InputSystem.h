/*********************************************************************************************
* Project: DirectXEngine
* File   : InputSystem
* Date   : 15.01.2023
* Author : Marcel Klein
*
* Setting up and managing the inputs from the user with the methodes to be executed. Designed as Singleton
* to be able to access it easier.
*
* Reference to: https://www.youtube.com/watch?v=zaJGn8pur5I&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=21
*
*********************************************************************************************/

#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"

class InputSystem
{
private:
	InputSystem();

	~InputSystem();

public:
	void Update();

	void AddListener(InputListener* listener);

	void RemoveListener(InputListener* listener);

	void SetCursorPosition(const Point& pos);

	void ShowCursor(bool show);

public:
	static InputSystem* Get();

	static void Create();

	static void Release();

private:
	std::unordered_set<InputListener*> m_set_listeners;

	unsigned char m_keys_state[256] = {};

	unsigned char m_old_keys_state[256] = {};

	Point m_old_mouse_pos;

	bool m_first_time = true;

	static InputSystem* m_system;
};

