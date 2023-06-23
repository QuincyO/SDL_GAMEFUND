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
#include "SoundManager.h"
#include "PlayButton.h"



//Begin Titlescreen

void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;

	//Loading Textures and Music
	TextureManager::Load("assets/Backgrounds/menuBackground.png", "TitleBackground");
	TextureManager::Load("assets/Images/Buttons/playSheet.png", "PlayButton");
	TextureManager::Load("assets/sprites/TitleSprite.png", "GameTitle");
	SoundManager::LoadMusic("assets/audio/Mutara.mp3", "TitleMusic");
	SoundManager::PlayMusic("TitleMusic");



	SDL_Rect source = { 0,0,4000,2000 };
	SDL_FRect dest = { 0, 0, Game::GetInstance().kWidth,Game::GetInstance().kHeight };

	m_objects.emplace("MenuBackground", new Static_Image(source, dest, "TitleBackground"));

	source = { 0,0,192,128 };
	dest = { Game::GetInstance().kWidth * .5f - source.w / 2,Game::GetInstance().kHeight * .75f,(float)source.w,(float)source.h };

	m_objects.emplace("PlayButton", new PlayButton(source, dest, "PlayButton"));

	source = { 0,0,1184,108 };
	dest = {Game::GetInstance().kWidth * .5f - source.w / 2, Game::GetInstance().kHeight * .15f, (float)source.w, (float)source.h};

	m_objects.emplace("GameTitle", new Static_Image(source, dest, "GameTitle"));




	}

	void TitleState::Update(float deltaTime)
	{
		if (EventManager::KeyPressed(SDL_SCANCODE_T))
		{
			std::cout << "Changing to GameState" << std::endl;
			StateManager::ChangeState(new GameState());//Change to new GameState
		}


		for (auto& object : m_objects)
		{
			object.second->Update(deltaTime);
		}
		if (timer > 3.1f)
		{
		}

		timer += deltaTime;

	}

	void TitleState::Render()
	{
		//std::cout << "Rendering Title Screen" << std::endl;
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::GetInstance().GetRenderer());

		for (auto& object : m_objects)
		{
			object.second->Render();
		}

	}

	void TitleState::Exit()
	{
		std::cout << "Exiting Title Screen" << std::endl;
		TextureManager::Unload("PlayButton");
		TextureManager::Unload("TitleBackground");
		SoundManager::UnloadMusic("TitleMusic");

		for (auto& object : m_objects)
		{
			delete object.second;
			object.second = nullptr;
		}
		m_objects.clear();



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