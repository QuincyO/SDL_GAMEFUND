#include "state.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>

//Begin Title

void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_T))
	{
		std::cout << "Changing to GameState" << std::endl;
		StateManager::ChangeState(new GameState());//Change to new GameState
	}
}

void TitleState::Render()
{
	std::cout << "Rendering Title Screen" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

}

void TitleState::Exit()
{
	std::cout << "Exiting Title Screen" << std::endl;
}