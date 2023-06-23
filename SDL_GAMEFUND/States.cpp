#include "state.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>
#include "MathManager.h"
#include "AnimatedSprite.h"
#include "TiledLevel.h"
#include "SpriteObject.h"
#include "EventManager.h"
#include "PlatformPlayer.h"
#include "CollisionManager.h"
#include "PlayButton.h"



//Begin Titlescreen

	void TitleState::Enter()
	{
		std::cout << "Entering TitleState..." << std::endl;


		timer = 0.0f;

	}

	void TitleState::Update(float deltaTime)
	{
		if (EventManager::KeyPressed(SDL_SCANCODE_T))
		{
			std::cout << "Changing to GameState" << std::endl;
			StateManager::ChangeState(new GameState());//Change to new GameState
		}
		if (timer > 3.1f)
		{
			StateManager::ChangeState(new MenuState());
		}

		timer += deltaTime;

	}

	void TitleState::Render()
	{
		//std::cout << "Rendering Title Screen" << std::endl;
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::GetInstance().GetRenderer());



	}

	void TitleState::Exit()
	{
		std::cout << "Exiting Title Screen" << std::endl;
		TextureManager::Unload("logo");


		m_pMUS = Mix_LoadMUS("assets/Caketown1.mp3");
		Mix_VolumeMusic(40);
		//Mix_PlayMusic(m_pMUS,-1);
	}
	//End of TitleScreen

//Start of GameScreen

void GameState::Enter()
{

	TextureManager::Load("assets/Images/Tiles.png", "tiles"); 
	TextureManager::Load("assets/Images/Player.png", "player");

	//TextureManager::Load("assets/real/background2.png", "gameBackground");
	//TextureManager::Load("assets/real/wasd.png", "wasd");
	////TextureManager::Load("assets/platformer/PNG/Player/p1_walk/spritesheet.png", "player");
	//TextureManager::Load("assets/platformer/PNG/Player/p2_stand.png", "blueGuy");


	m_objects.emplace("level", new TiledLevel(24, 32, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Level1.txt", "tiles"));
	m_objects.emplace("player", new PlatformPlayer({ 0,0,128,128 }, { 288,480,64,64 }));


	//Mix_PlayMusic(gameMusic, -1);


	

}

void GameState::Update(float deltaTime)
{

	if (EventManager::KeyPressed(SDL_SCANCODE_X))
	{
		StateManager::ChangeState(new TitleState());
	}

	else if (EventManager::KeyPressed(SDL_SCANCODE_P))
	{
		StateManager::PushState(new PauseState());
	}
	else
	{

	
		for (auto objects : m_objects)
		{
			objects.second->Update(deltaTime);
		}


		for (unsigned int i = 0; i < static_cast<TiledLevel*>(m_objects["level"])->GetObstacles().size(); i++)
		{
			SDL_FRect* obstacleColliderTransform = static_cast<TiledLevel*>(m_objects["level"])->GetObstacles()[i]->GetDestinationTransform();

			float obstacleLeft = obstacleColliderTransform->x;
			float obstacleRight = obstacleColliderTransform->x + obstacleColliderTransform->w;
			float obstacleTop = obstacleColliderTransform->y;
			float obstacleBottom = obstacleColliderTransform->y + obstacleColliderTransform->h;

			SDL_FRect* PlayerColliderTransform = m_objects["player"]->GetDestinationTransform();

			float playerLeft = PlayerColliderTransform->x;
			float playerRight = PlayerColliderTransform->x + PlayerColliderTransform->w;
			float playerTop = PlayerColliderTransform->y;
			float playerBottom = PlayerColliderTransform->y + PlayerColliderTransform->h;


			//Checking horizontal overlap by comparing right vs left andleft vs right
			bool xOverLap = playerLeft<obstacleRight&& playerRight>obstacleLeft;

			//Checking Vertical overlap by comparing top vs bottom and bottom vs top
			bool yOverLap = playerTop <obstacleBottom&& playerBottom>obstacleTop;

			//Used to determine which direction the colliusion came from
			float bottomCollision = obstacleBottom - PlayerColliderTransform->y;
			float topCollision = playerBottom - obstacleColliderTransform->y;
			float leftCollision = playerRight - obstacleColliderTransform->x;
			float rightCollision = obstacleRight - PlayerColliderTransform->x;

			if (xOverLap && yOverLap)
			{
				PlatformPlayer* pPlayer = static_cast<PlatformPlayer*> (m_objects["player"]);

				//Top Collision
				if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
				{
					pPlayer->StopY();
					pPlayer->SetY(PlayerColliderTransform->y - topCollision);
					pPlayer->SetGrounded(true);
				}
				//Bottom Collision
				if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
				{
					pPlayer->StopY();
					pPlayer->SetY(PlayerColliderTransform->y + bottomCollision);
				}
				//Left Collision
				if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
				{
					pPlayer->StopX();
					pPlayer->SetX(PlayerColliderTransform->x - leftCollision);
				}
				//Right Collision
				if ((rightCollision < leftCollision) && (rightCollision < bottomCollision) && (rightCollision < topCollision))
				{
					pPlayer->StopX();
					pPlayer->SetX(PlayerColliderTransform->x + rightCollision);
				}

			}
		}
	}


	if (EventManager::KeyPressed(SDL_SCANCODE_0))
	{
		StateManager::ChangeState(new WinState);

	}


	timer += deltaTime;
		
	
}

void GameState::Render()
{
	//std::cout << "Rendering Gamestate..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	for (auto objects : m_objects)
	{
		objects.second->Render();
	}

}

void GameState::Exit()
{
	std::cout<<"Exiting GameState.." << std::endl;
	TextureManager::Unload("tiles");

	for (auto objects : m_objects)
	{
		delete objects.second;
	}
	m_objects.clear();
	Mix_FreeMusic(gameMusic);
	gameMusic = nullptr;
}

void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;

	Mix_ResumeMusic();
	

}

//End of GameScreen
//Start of Pause Screen
void PauseState::Enter()
{
	std::cout << "Entering Pause State..." << std::endl;
	TextureManager::Load("assets/real/Pause.png", "pauseTitle");
	TextureManager::Load("assets/real/Resume.png", "resumeButton");
	SDL_Rect tRect;
	SDL_FRect frect;



	Mix_PauseMusic();

}

void PauseState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_R))
	{
		StateManager::PopState();
	}
}

void PauseState::Render()
{
	//std::cout << "Rendering Pause State" << std::endl;
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
	TextureManager::Load("assets/real/Background.png", "background");
	TextureManager::Load("assets/real/Credits.png", "credit");
	TextureManager::Load("assets/real/Game.png", "game");
	TextureManager::Load("assets/real/Name.png", "name");
	TextureManager::Load("assets/Images/Buttons/play.png", "PlayButton");

	int buttonWidth = 400;
	int buttonHeight = 100;

	float buttonX = Game::GetInstance().kWidth / 2.0f - buttonWidth/2.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f - buttonHeight / 2.0f;

	SDL_Rect source = { 0,0,buttonWidth,buttonHeight };
	SDL_FRect dest = { buttonX,buttonY,(float)buttonWidth,(float)buttonHeight };
	m_objects.emplace("PlayButton", new PlayButton(source, dest, "PlayButton"));





}

void MenuState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_C)) {
		StateManager::ChangeState(new CreditState);
	}
	for (auto object : m_objects)
	{
		object.second->Update(deltaTime);
		if (StateManager::isStateChanging())
		{
			break;
		}
	}
}

void MenuState::Render()
{

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 0, 128, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	m_objects["PlayButton"]->Render();
}

void MenuState::Exit()
{
	std::cout << "Exiting Menu Screen" << std::endl;

	TextureManager::Unload("PlayButton");

	for (auto objects : m_objects)
	{
		delete objects.second;
		objects.second = nullptr;
	}
	m_objects.clear();

}

void MenuState::Resume()
{
	std::cout << "Resuming Menu Screen" << std::endl;
}//End of MenuState

//Start of CreditState

void CreditState::Enter()
{
	std::cout << "Entering Credit State" << std::endl;
	SDL_Rect rect;
	SDL_FRect frect;
	TextureManager::Load("assets/real/Credit.png", "creditTitle");
	TextureManager::Load("assets/real/menu.png", "menuButton");
	TextureManager::Load("assets/real/Quincy.png", "quincy");


}

void CreditState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_ESCAPE))
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
	SDL_Rect rect;
	SDL_FRect frect;
	TextureManager::Load("assets/real/Win.png", "winTitle");
	TextureManager::Load("assets/real/SpaceMenu.png", "restartButton");



	
}

void WinState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE))
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


	m_pMUS = Mix_LoadMUS("assets/Caketown1.mp3");
	Mix_VolumeMusic(40);
	Mix_PlayMusic(m_pMUS, -1);
}

void WinState::Resume()
{
	std::cout << "Resuming Win State" << std::endl;
}

void LoseState::Enter()
{
	std::cout << "Entering Lose State" << std::endl;
	SDL_Rect rect;
	SDL_FRect frect;
	TextureManager::Load("assets/real/Lost.png", "lossTitle");
	TextureManager::Load("assets/real/SpaceMenu.png", "restartButton");



}


void LoseState::Render()
{
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState" << std::endl;


	m_pMUS = Mix_LoadMUS("assets/Caketown1.mp3");
	Mix_VolumeMusic(40);
	Mix_PlayMusic(m_pMUS, -1);

}

void LoseState::Resume()
{
	std::cout << "Resuming Lose State" << std::endl;
}