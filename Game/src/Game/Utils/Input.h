#ifndef INPUT_H
#define INPUT_H

#include <IEventReceiver.h>
#include <vector2d.h>

namespace game
{
	class Input : public irr::IEventReceiver
	{
	public:
		struct SMouseState
		{
			irr::core::vector2di Position;
			bool LeftButtonDown;
			bool RightButtonDown;
			bool MiddleButtonDown;

			SMouseState() : Position(0, 0), LeftButtonDown(false), RightButtonDown(false), MiddleButtonDown(false) {}
		} MouseState;
		
		Input();

		virtual bool OnEvent(const irr::SEvent& p_event);

		const SMouseState& GetMouseState() const { return MouseState; }

		virtual bool IsKeyDown(irr::EKEY_CODE p_keyCode) const;

	private:
		bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}

#endif // !INPUT_H

