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
	SoundManager::SetMusicVolume(60);



	SDL_Rect source = { 0,0,4000,2000 };
	SDL_FRect dest = { 0, 0, Game::GetInstance().kWidth,Game::GetInstance().kHeight };

	m_objects.emplace("MenuBackground", new Static_Image(source, dest, "TitleBackground"));

	source = { 0,0,192,128 };
	dest = { Game::GetInstance().kWidth * .5f - source.w / 2,Game::GetInstance().kHeight * .8f,(float)source.w,(float)source.h };

	m_objects.emplace("PlayButton", new PlayButton(source, dest, "PlayButton"));

	source = { 0,0,1184,108 };
	dest.w = (float)source.w / 2;
	dest.h = (float)source.h / 2;
	dest.x = Game::GetInstance().kWidth * .5f - dest.w / 2;
	dest.y = Game::GetInstance().kHeight * .15f;

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
			if (StateManager::IsStateChaning())
			{
				return;
			}
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

		SoundManager::StopMusic();

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
		//Loading Music
		SoundManager::LoadMusic("assets/spaceGame/ObservingTheStar.ogg", "GameMusic");

		//Loading Sounds
		SoundManager::LoadSound("assets/spaceGame/weaponfire6.wav", "ShootFX1");
		SoundManager::LoadSound("assets/spaceGame/laserSmall_000.ogg", "ShootFX2");
		SoundManager::LoadSound("assets/spaceGame/laserSmall_002.ogg", "ShootFX3");
		SoundManager::LoadSound("assets/spaceGame/lowFrequency_explosion_000.ogg", "HitSound1");
		SoundManager::LoadSound("assets/spaceGame/lowFrequency_explosion_001.ogg", "HitSound2");


		//Loading Background Images
			//3 Slowest 20px/s
		TextureManager::Load("assets/Backgrounds/nebulawetstars.png", "BackgroundLayer3");
		//2 Medium 60px/s
		TextureManager::Load("assets/Backgrounds/nebuladrystars.png", "BackgroundLayer2");
		//1 Fastest 150px/s 
		TextureManager::Load("assets/Backgrounds/nebula2.png", "BackgroundLayer1"); //Animated

		//Loading Player + EnemyPlayer Images
		TextureManager::Load("assets/PNG/playerShip1_red.png", "Player");
		TextureManager::Load("assets/PNG/enemyShip.png", "Enemy");

		//Loading Explosions and Bullets
		TextureManager::Load("assets/bigBooms/1.png", "Explosion1");
		TextureManager::Load("assets/bigBooms/2.png", "Explosion2");
		TextureManager::Load("assets/bigBooms/3.png", "Explosion3");
		TextureManager::Load("assets/bigBooms/4.png", "Explosion4");
		TextureManager::Load("assets/PNG/laserGreen.png", "EnemyLaser");
		TextureManager::Load("assets/PNG/laserRed.png", "PlayerLaser");

		SDL_Rect source = { 0,0,0,0 };
		SDL_FRect dest = { 0,0,896,1024 };

		SDL_QueryTexture(TextureManager::GetTexture("BackgroundLayer3"), NULL, NULL, &source.w, &source.h);
		dest.w = 896;
		dest.h = 1024;
		m_backgroundObjects.push_back( new Static_Image(source, dest, "BackgroundLayer3", 20));
		dest.y = -dest.h;
		m_backgroundObjects.push_back( new Static_Image(source, dest, "BackgroundLayer3", 20));

		SDL_QueryTexture(TextureManager::GetTexture("BackgroundLayer2"), NULL, NULL, &source.w, &source.h);
		dest.y = 500;
		m_backgroundObjects.push_back( new Static_Image(source, dest, "BackgroundLayer2", 60));
		dest.y = 500 - dest.h;
		m_backgroundObjects.push_back( new Static_Image(source, dest, "BackgroundLayer2", 60));

		SDL_QueryTexture(TextureManager::GetTexture("BackgroundLayer1"), NULL, NULL, &source.w, &source.h);
		source.w = 1060;
		dest.y = -dest.h;
		m_backgroundObjects.push_back( new Animated_Image(source, dest, "BackgroundLayer1", 150,2));




}

void GameState::Update(float deltaTime)
{
	for (auto objects : m_backgroundObjects)
	{
		objects->Update(deltaTime);
	}

	timer += deltaTime;
}

void GameState::Render()
{
	//std::cout << "Rendering Gamestate..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	for (auto objects : m_backgroundObjects)
	{
		objects->Render();
	}

}

void GameState::Exit()
{
	std::cout<<"Exiting GameState.." << std::endl;

	for (auto objects : m_backgroundObjects)
	{
		delete objects;
	}
	m_backgroundObjects.clear();
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