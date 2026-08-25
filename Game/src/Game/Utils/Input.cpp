#include "Input.h"

namespace game
{
	Input::Input()
	{
		for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		{
			m_keyIsDown[i] = false;
		}
	}

	bool Input::OnEvent(const irr::SEvent& p_event)
	{
		if (p_event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			m_keyIsDown[p_event.KeyInput.Key] = p_event.KeyInput.PressedDown;
		}
		else if (p_event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (p_event.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;
			case irr::EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				MouseState.RightButtonDown = true;
				break;
			case irr::EMIE_RMOUSE_LEFT_UP:
				MouseState.RightButtonDown = false;
				break;
			case irr::EMIE_MMOUSE_PRESSED_DOWN:
				MouseState.MiddleButtonDown = true;
				break;
			case irr::EMIE_MMOUSE_LEFT_UP:
				MouseState.MiddleButtonDown = false;
				break;
			case irr::EMIE_MOUSE_MOVED:
				MouseState.Position.X = p_event.MouseInput.X;
				MouseState.Position.Y = p_event.MouseInput.Y;
				break;
			default:
				break;
			}
		}
		return false;
	}
	bool Input::IsKeyDown(irr::EKEY_CODE p_keyCode) const
	{
		return m_keyIsDown[p_keyCode];
	}
}