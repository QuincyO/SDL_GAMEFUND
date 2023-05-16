#pragma once
#include <SDL.h>
#include <iostream>
#include "StateManager.h"
#include "state.h"


class Game
{
private:
	static const int kWidth = 1024;
	static const int kHeight = 768;
	static const int kRectangleSpeed = 600;
	Game();
public:
	static Game& GetInstance();

	int Init(const char* Title);

	SDL_Renderer* GetRenderer();

	bool IsRunning();
	void HandleEvents();
	bool KeyDown(SDL_Scancode key) ;
	void Update(float deltaTime) ;
	void Render() ;
	void Clean();


private:
	SDL_Renderer* p_Renderer;
	SDL_Window* p_Window;

	SDL_FRect m_RectangleTransform;
	const Uint8* m_keyStates;

	bool m_running;
	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;

};

