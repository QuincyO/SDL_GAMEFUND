#pragma once
#include <SDL.h>
#include <iostream>
#include "StateManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "state.h"


class Game
{
private:

	Game();
public:
	static const int kWidth = 1280;
	static const int kHeight = 720;
	static Game& GetInstance();

	int Init(const char* Title);

	SDL_Renderer* GetRenderer();

	bool IsRunning();
	void Quit();
	void HandleEvents();
	void Update(float deltaTime) ;
	void Render() ;
	void Clean();


private:
	SDL_Renderer* p_Renderer;
	SDL_Window* p_Window;

	const Uint8* m_keyStates;

	bool m_running;
	int SCREEN_HEIGHT;
	int SCREEN_WIDTH;

};

