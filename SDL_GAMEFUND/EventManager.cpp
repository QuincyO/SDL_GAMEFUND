#include "EventManager.h"
#include "Game.h"
#include <cstring>
#include <iostream>

void EventManager::Init()
{
	s_currentKeyState = SDL_GetKeyboardState(&s_numKeys);
	s_lastKeyState = new Uint8[s_numKeys];
	std::memcpy(s_lastKeyState, s_currentKeyState, s_numKeys);
	s_currentMouseState = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
	s_lastMouseState = s_currentMouseState;
	std::cout << "EventManager Init Done!" << std::endl;
}

void EventManager::HandleEvents()
{
	SDL_Event event;
	std::memcpy(s_lastKeyState, s_currentKeyState, s_numKeys);
	s_lastMouseState = s_currentMouseState;
	s_lastKeyDown = -1;
	s_lastKeyUp;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::GetInstance().Clean();
			break;
		case SDL_KEYDOWN:
			s_lastKeyDown = event.key.keysym.sym;
			break;
		case SDL_KEYUP:
			s_lastKeyUp = event.key.keysym.sym;
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				Game::GetInstance().Clean();
			}
			break;

		}
	}
	s_currentKeyState = SDL_GetKeyboardState(&s_numKeys);
	s_currentMouseState = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
}


bool EventManager::KeyHeld(const SDL_Scancode key)
{
	if (s_currentKeyState)
	{
		return s_currentKeyState[key] == 1;
	}
	return false;
}

bool EventManager::KeyPressed(const SDL_Scancode key)
{
	return (s_currentKeyState[key] > s_lastKeyState[key]);
}

bool EventManager::KeyReleased(const SDL_Scancode key)
{
	return (s_currentKeyState[key] < s_lastKeyState[key]);
}