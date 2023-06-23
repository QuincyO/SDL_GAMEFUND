#include "PlayButton.h"
#include "StateManager.h"
#include "EventManager.h"
#include "state.h"

PlayButton::PlayButton(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	:UI_Button(source,destination,textureKey)
{
	SoundManager::LoadSound("assets/Sound/Effects/button1.ogg", "ClickSound");
}

void PlayButton::Update(float deltaTime)
{
		SDL_Rect intDestinationRect = { (int)m_destinationTransform.x,(int)m_destinationTransform.y,(int)m_destinationTransform.w,(int)m_destinationTransform.h };
		bool mouseOverLap = SDL_PointInRect(&EventManager::GetMousePosition(), &intDestinationRect);
		switch (m_state)
		{
		case ButtonState::STATE_UP:
			if (mouseOverLap && EventManager::MousePressed(1))
			{
				m_state = ButtonState::STATE_DOWN;
				EventManager::SetCursor(SDL_SYSTEM_CURSOR_HAND);
			}
			break;
		case ButtonState::STATE_DOWN:
			if (EventManager::MouseReleased(1))
			{
				if (mouseOverLap)
				{
					m_state = ButtonState::STATE_OVER;
					Execute();
				}
				else
				{
					m_state = ButtonState::STATE_UP;
					EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
				}
			}
			break;
		}

	}

void PlayButton::Execute()
{
	StateManager::ChangeState(new GameState());
}