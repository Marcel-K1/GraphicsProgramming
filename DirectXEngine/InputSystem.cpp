#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_system = nullptr;

//As Singleton
InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}

void InputSystem::Update()
{
	//MOUSE MOVEMENT
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//MOUSE MOVE EVENT
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);


	//KEYBOARD AND MOUSE BUTTONS
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			//KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else //KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}

			}

		}

		//Store current keys state to old keys state buffer:
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::AddListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::SetCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::ShowCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::Get()
{
	return m_system;
}

void InputSystem::Create()
{
	if (InputSystem::m_system) throw std::exception("InputSystem already created");
	InputSystem::m_system = new InputSystem();
}

void InputSystem::Release()
{
	if (!InputSystem::m_system) return;
	delete InputSystem::m_system;
}