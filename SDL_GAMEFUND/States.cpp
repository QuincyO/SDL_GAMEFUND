#include "state.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>
#include "MathManager.h"
#include "AnimatedSprite.h"

//Begin Titlescreen

void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;
	timer = 0.0f;

}

void TitleState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_T))
	{
		std::cout << "Changing to GameState" << std::endl;
		StateManager::ChangeState(new GameState());//Change to new GameState
	}
	if (timer > 4.0f)
	{
		StateManager::ChangeState(new MenuState());
	}

	timer += deltaTime;
	
}

void TitleState::Render()
{
	//std::cout << "Rendering Title Screen" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, 255);
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
	/*
	m_gameObjects.push_back(new GameObject(100, 100, 30, 30));
	m_gameObjects.push_back(new GameObject(400, 100, 30, 30));
	m_gameObjects.push_back(new GameObject(600, 100, 30, 30));
	//*/

	killBox = new GameObject(500, 800, 30, 30, 255, 0, 0, 255);

	SDL_Rect srcTrans = { 0,0,64,64 };


	m_gameObjects.push_back(new AnimatedSprite(0,1,3,srcTrans,{100,100,64,64 }));
	m_gameObjects.push_back(new AnimatedSprite(0, 1, 3, srcTrans, { 400,100,64,64 }));
	m_gameObjects.push_back(new AnimatedSprite(0,1,3,srcTrans,{700,100,64,64 }));


	m_player = (new GameObject(250,250,100,100));
	m_timer = 0.0f;
	/*
	SDL_Surface* pImageSurface = IMG_Load("AssetFilePath");
	if (pImageSurface == NULL)
	{
		std::cout << "Failed to load Image" << std::endl;
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), pImageSurface);
		SDL_FreeSurface(pImageSurface);
	}
	*/
	m_playerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/goomba.png");
	m_objectTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/portal.png");

	//m_pMusic = Mix_LoadMUS("assets/MainMenu.mp3");
	//Mix_PlayMusic(m_pMusic, -1);


}

void GameState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();


	if  (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		StateManager::PushState(new PauseState());
	}

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


		 for (std::vector<AnimatedSprite*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
		 {
			 AnimatedSprite* itObject = *it;

			
			 
				 if (SDL_HasIntersectionF(&m_player->GetTransform(), &killBox->GetTransform()))
				 {
					 it = m_gameObjects.erase(it);
					 delete itObject;
					 itObject = nullptr;
					 it++;
					 StateManager::ChangeState(new LoseState);
					 break;
				 }
				 if (SDL_HasIntersectionF(&m_player->GetTransform(), &itObject->GetDestinationTransform()))
				 {
					 it = m_gameObjects.erase(it);
					 delete itObject;
					 itObject = nullptr;
					 StateManager::ChangeState(new LoseState);
					 break;

				 }
				 else
				 {
					 it++;
				 }
			 
	



		 }


		 for (AnimatedSprite* objects : m_gameObjects)
		 {
			 objects->Animate(deltaTime);
		 }
	
	if (m_timer > 20.0f)
	{
		StateManager::ChangeState(new WinState);
	}




		
	m_timer += deltaTime;
	
}

void GameState::Render()
{
	//std::cout << "Rendering Gamestate..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	for (AnimatedSprite*object : m_gameObjects)
	{

			SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), m_objectTexture, &object->GetSourceTransform(), &object->GetDestinationTransform(),
				object->GetAngle(), 0, SDL_FLIP_NONE);
		
	}

	SDL_Rect playerRect = MathManager::ConvertFRect2Rect(m_player->GetTransform());
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), m_playerTexture, NULL, &playerRect);
}

void GameState::Exit()
{
	std::cout<<"Exiting GameState.." << std::endl;
	for (AnimatedSprite* Objects : m_gameObjects)
	{
		delete Objects;
		Objects = nullptr;
	}
	delete m_player;
	m_player = nullptr;

	delete killBox;
	killBox = nullptr;

	SDL_DestroyTexture(m_objectTexture);
	SDL_DestroyTexture(m_playerTexture);

	//Mix_FreeMusic(m_pMusic);
	//m_pMusic = nullptr;
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
	if (Game::GetInstance().GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		StateManager::PopState();
	}
}

void PauseState::Render()
{
	//std::cout << "Rendering Pause State" << std::endl;
	SDL_Rect rect = { 256,128,512,512 };
	//First Render the Gamestate
	StateManager::GetStates().front()->Render();

	//Now Render the Rest of PauseState
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
}

void PauseState::Exit()
{
	std::cout << "Exiting Pause State..." << std::endl;

}


//Start of Menu Screen
void MenuState::Enter()
{
	std::cout << "Rendering Menu Screen" << std::endl;

}

void MenuState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C)) {
		StateManager::ChangeState(new CreditState);
	}

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))
	{
		StateManager::ChangeState(new GameState);
	}
}

void MenuState::Render()
{

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 0, 128, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void MenuState::Exit()
{
	std::cout << "Exiting Menu Screen" << std::endl;
}

void MenuState::Resume()
{
	std::cout << "Resuming Menu Screen" << std::endl;
}//End of MenuState

//Start of CreditState

void CreditState::Enter()
{
	std::cout << "Entering Credit State" << std::endl;
}

void CreditState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		StateManager::ChangeState(new MenuState);
	}
}

void CreditState::Render()
{
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 192, 203, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void CreditState::Exit()
{
	std::cout << "Exiting Credit State" << std::endl;
}

void CreditState::Resume()
{
	std::cout << "Resuming Creit State" << std::endl;
}

void WinState::Enter()
{
	std::cout << "Enteriing Win State" << std::endl;
}

void WinState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_SPACE))
	{
		StateManager::ChangeState(new MenuState);
	}
}


void WinState::Render()
{
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void WinState::Exit()
{
	std::cout << "Exiting Win State" << std::endl;
}

void WinState::Resume()
{
	std::cout << "Resuming Win State" << std::endl;
}

void LoseState::Enter()
{
	std::cout << "Entering Lose State" << std::endl;

}

void LoseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_SPACE))
	{
		StateManager::ChangeState(new MenuState);
	}
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState" << std::endl;
}

void LoseState::Resume()
{
	std::cout << "Resuming Lose State" << std::endl;
}