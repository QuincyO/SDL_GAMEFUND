#include "UI_Button.h"
#include "Game.h"
#include "TextureManager.h"
#include "EventManager.h"

UI_Button::UI_Button(SDL_Rect source, SDL_FRect destination, const char* textureKey,const char* buttonText)
	:SpriteObject(source, destination,textureKey),
	m_state(ButtonState::STATE_UP),
	buttonText{buttonText}
{
	m_font = TTF_OpenFont("assets/fonts/kenpixel_blocks.ttf", 36);
	if (m_font == NULL)
	{
		std::cout << "Font Failed to Load: " << SDL_GetError() << endl;
	}
}

void UI_Button::Render()
{
	if (m_state == ButtonState::STATE_UP)
	{
		m_sourceTransform.y = m_sourceTransform.h * 0;
	}
	if (m_state == ButtonState::STATE_OVER)
	{
		m_sourceTransform.y = m_sourceTransform.h * 1;
	}
	if (m_state == ButtonState::STATE_DOWN)
	{
		m_sourceTransform.y = m_sourceTransform.h * 2;
	}

	SDL_Rect source = { 0,0,0,0 };
	source.x = 0;
	source.y = 0;
	source.w = (int)m_destinationTransform.w;
	source.h = (int)m_destinationTransform.h;

	SDL_FRect dest = { 0,0,0,0 };
	dest.w = source.w / 2;
	dest.h = source.h / 2;

	dest.x = m_destinationTransform.x + dest.w / 2;

	dest.y = m_destinationTransform.y + dest.h / 2;

	SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform, 0, 0, SDL_FLIP_NONE);


	SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::LoadString(buttonText, "ResumeText"), &source, &dest, 0, 0, SDL_FLIP_NONE);
}

void UI_Button::Update(float deltaTime)
{
	SDL_Rect intDestinationRect = { (int)m_destinationTransform.x,(int)m_destinationTransform.y,(int)m_destinationTransform.w,(int)m_destinationTransform.h };
	bool mouseOverLap = SDL_PointInRect(&EventManager::GetMousePosition(), &intDestinationRect);
	switch (m_state)
	{
	case ButtonState::STATE_UP:
		if (mouseOverLap)
		{
			m_state = ButtonState::STATE_OVER;
			EventManager::SetCursor(SDL_SYSTEM_CURSOR_HAND);
		}
		break;
	case ButtonState::STATE_OVER:
		if (!mouseOverLap)
		{
			m_state = ButtonState::STATE_UP;
			EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
		}
		else if (mouseOverLap && EventManager::MousePressed(1))
		{
			m_state = ButtonState::STATE_DOWN; //1 is left mouse
		}
		break;
	case ButtonState::STATE_DOWN:
		if (EventManager::MouseReleased(1))
		{
			if (mouseOverLap)
			{
				m_state = ButtonState::STATE_OVER;
				EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
				SoundManager::PlaySound("Click");
				Execute();
			}
			else
			{
				m_state = ButtonState::STATE_OVER;
				EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			}
		}
		break;
	}

}

