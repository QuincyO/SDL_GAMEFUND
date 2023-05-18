#include "state.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>

//Begin Titlescreen

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
//End of TitleScreen

//Start of GameScreen

void GameState::Enter()
{
	m_gameObjects.push_back(new GameObject(100, 100, 30, 30));
	m_gameObjects.push_back(new GameObject(400, 100, 30, 30));
	m_gameObjects.push_back(new GameObject(600, 100, 30, 30));

	m_player = (new GameObject(250, 250, 50, 50,255,0,255,255));
	m_gameObjects.push_back(m_player);

}

void GameState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_H))
	{
		StateManager::ChangeState(new TitleState());
	}
	else if  (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		StateManager::PushState(new PauseState());
	}
	else
	{
		if (GameInstance.KeyDown(SDL_SCANCODE_A))
		{
			m_player->UpdatePositionX(-kPlayerSpeed*deltaTime);
		}
		 if (GameInstance.KeyDown(SDL_SCANCODE_D))
		{
			m_player->UpdatePositionX(kPlayerSpeed * deltaTime);
		}
		 if (GameInstance.KeyDown(SDL_SCANCODE_W))
		{
			m_player->UpdatePositionY(-kPlayerSpeed * deltaTime);
		}
		 if (GameInstance.KeyDown(SDL_SCANCODE_S))
		{
			m_player->UpdatePositionY(kPlayerSpeed * deltaTime);
		}
	}

		
	
}

void GameState::Render()
{
	std::cout << "Rendering Gamestate..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	for (GameObject*object : m_gameObjects)
	{
		object->Draw(Game::GetInstance().GetRenderer());
	}
	SDL_RenderPresent(Game::GetInstance().GetRenderer());
}

void GameState::Exit()
{
	std::cout<<"Exiting GameState.." << std::endl;
	for (GameObject* Objects : m_gameObjects)
	{
		delete Objects;
		Objects = nullptr;
	}
}

void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
}

//End of GameScreen

//Start of Pause Screen
void PauseState::Enter()
{
	std::cout << "Entering Pause State..." << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (Game::GetInstance().GetInstance().KeyDown(SDL_SCANCODE_R))
	{
		StateManager::PopState();
	}
}

void PauseState::Render()
{
	std::cout << "Rendering Pause State" << std::endl;
	//First Render the Gamestate
	StateManager::GetStates().front()->Render();

	//Now Render the Rest of PauseState
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256,128,512,512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
}

void PauseState::Exit()
{
	std::cout << "Exiting Pause State..." << std::endl;

}