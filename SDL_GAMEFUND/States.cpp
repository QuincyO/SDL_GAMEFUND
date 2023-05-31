#include "state.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>
#include "MathManager.h"
#include "AnimatedSprite.h"
#include "TiledLevel.h"
#include "SpriteObject.h"
#include "CollisionManager.h"



//Begin Titlescreen

	void TitleState::Enter()
	{
		std::cout << "Entering TitleState..." << std::endl;
		SDL_Rect Rect = {
			0,0,
			1024,
			1024
		};


		SDL_FRect fRect = {

			(1280 / 2) - (Rect.w * .75 / 2), //Position X-Axis
			(720 / 2) - (Rect.h * .7 / 2), //Position Y-Axis
			Rect.w * .75, //Width Size
			Rect.h * .7 //Height Size
		};
		m_spriteLogo = new SpriteObject(Rect, fRect);


		TextureManager::Load("assets/real/Logo.png", "logo");
		m_pMix = Mix_LoadWAV("assets/real/gmae.wav");

		//Mix_VolumeChunk(m_pMusic, 100);
		std::cout << Mix_PlayChannel(1, m_pMix, 0) << std::endl;

		timer = 0.0f;

	}

	void TitleState::Update(float deltaTime)
	{
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_T))
		{
			std::cout << "Changing to GameState" << std::endl;
			StateManager::ChangeState(new MenuState());//Change to new GameState
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


		SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("logo"), m_spriteLogo->GetSourceTransform(), m_spriteLogo->GetDestinationFTransform());

	}

	void TitleState::Exit()
	{
		std::cout << "Exiting Title Screen" << std::endl;
		TextureManager::Unload("logo");
		delete m_spriteLogo;
		m_spriteLogo = nullptr;

		m_pMUS = Mix_LoadMUS("assets/Caketown1.mp3");
		Mix_VolumeMusic(40);
		Mix_PlayMusic(m_pMUS,-1);
	}
	//End of TitleScreen

//Start of GameScreen

void GameState::Enter()
{

	TextureManager::Load("assets/Images/Tiles.png", "tiles");
	TextureManager::Load("assets/real/background2.png", "gameBackground");
	TextureManager::Load("assets/real/wasd.png", "wasd");
	TextureManager::Load("assets/platformer/PNG/Player/p1_walk/spritesheet.png", "player");
	TextureManager::Load("assets/platformer/PNG/Player/p2_stand.png", "blueGuy");
	SDL_Rect rect;
	SDL_FRect frect;

	SDL_QueryTexture(TextureManager::GetTexture("gameBackground"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;


	frect.x = 0;
	frect.y = 0;
	frect.w = rect.w;
	frect.h = rect.h;
	m_background = new SpriteObject(rect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("wasd"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;


	frect.x = 1280 * .8;
	frect.y = 720 * .05;
	frect.w = rect.w/2;
	frect.h = rect.h/2;
	m_button = new SpriteObject(rect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("blueGuy"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;


	frect.x = 1280 * .25;
	frect.y = 720 * .25;
	frect.w = rect.w ;
	frect.h = rect.h ;
	m_object = new SpriteObject(rect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("player"), NULL, NULL, &rect.x, &rect.y);
	rect.x = 0;
	rect.y = 0;
	rect.w=72;
	rect.h;


	frect.x = 1280 * .5;
	frect.y = 720 * .5;
	frect.w = rect.w ;
	frect.h = rect.h ;
	m_player = new AnimatedSprite(NULL, .1, 11, rect, frect);


	gameMusic = Mix_LoadMUS("assets/MainMenu.mp3");

	Mix_PlayMusic(gameMusic, -1);



	m_pLevel = new TiledLevel(24, 32, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Level1.txt", "tiles");


}

void GameState::Update(float deltaTime)
{
	m_pLevel->Update(deltaTime);
	m_player->Animate(deltaTime);


	if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		StateManager::PushState(new PauseState());
	}



	if (Game::GetInstance().KeyDown(SDL_SCANCODE_W))
	{
		m_object->UpdateYPosition(-kPlayerSpeed * deltaTime);
	}
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_S))
	{
		m_object->UpdateYPosition(kPlayerSpeed * deltaTime);
	}

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_A))
	{
		m_object->UpdateXPosition(-kPlayerSpeed * deltaTime);
	}

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_D))
	{
		m_object->UpdateXPosition(kPlayerSpeed * deltaTime);
	}


	if (CollisionManager::AABBCheck(*m_object->GetDestinationFTransform(), *m_player->GetDestinationFTransform()))
	{
		StateManager::ChangeState(new LoseState);
	}


	if (Game::GetInstance().KeyDown(SDL_SCANCODE_0))
	{
		StateManager::ChangeState(new WinState);

	}
	if (timer > 5)
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



	m_pLevel->Render();

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("gameBackground"), m_background->GetSourceTransform(), m_background->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("wasd"), m_button->GetSourceTransform(), m_button->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("blueGuy"), m_object->GetSourceTransform(), m_object->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("player"), m_player->GetSourceTransform(), m_player->GetDestinationFTransform());

}

void GameState::Exit()
{
	std::cout<<"Exiting GameState.." << std::endl;
	TextureManager::Unload("tiles");

	delete m_background;
	delete m_button;
	delete m_object;
	delete m_player;

	m_background = nullptr;
	m_button = nullptr;
	m_object = nullptr;
	m_player = nullptr;

	delete m_pLevel;
	m_pLevel = nullptr;


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

	SDL_QueryTexture(TextureManager::GetTexture("pauseTitle"), NULL, NULL, &tRect.w, &tRect.h);
	tRect.x = 0;
	tRect.y = 0;
	tRect.w;
	tRect.h;


	frect.x = rect.x + (rect.w/2) - (tRect.w/2);
	frect.y = rect.y;
	frect.w = tRect.w ;
	frect.h = tRect.h;
	m_pause = new SpriteObject(tRect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("resumeButton"), NULL, NULL, &tRect.w, &tRect.h);
	tRect.x = 0;
	tRect.y = 0;
	tRect.w;
	tRect.h;


	frect.x = rect.x + (rect.w / 2) - (tRect.w / 4);
	frect.y = rect.y + rect.h*.85;
	frect.w = tRect.w/2;
	frect.h = tRect.h/2;
	m_button = new SpriteObject(tRect, frect);

	Mix_PauseMusic();

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
	//First Render the Gamestate
	StateManager::GetStates().front()->Render();

	//Now Render the Rest of PauseState
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("pauseTitle"), m_pause->GetSourceTransform(), m_pause->GetDestinationFTransform());

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("resumeButton"), m_button->GetSourceTransform(), m_button->GetDestinationFTransform());


}

void PauseState::Exit()
{
	std::cout << "Exiting Pause State..." << std::endl;
	delete m_pause;
	delete m_button;
	m_pause = nullptr;
	m_button = nullptr;

}


//Start of Menu Screen
void MenuState::Enter()
{
	std::cout << "Rendering Menu Screen" << std::endl;
	TextureManager::Load("assets/real/Background.png", "background");
	TextureManager::Load("assets/real/Credits.png", "credit");
	TextureManager::Load("assets/real/Game.png", "game");
	TextureManager::Load("assets/real/Name.png", "name");



	SDL_Rect rect =
	{
		0,0,
		1280,
		720
	};
	SDL_FRect frect =
	{
		0,0,1280,720
	};

	m_backGround = new SpriteObject(rect, frect);
	
	rect.x = 0;
	rect.y = 0;
	rect.w = 587;
	rect.h = 79;
	

	frect.x = 1280*.25 - rect.w/2;
	frect.y =720*.85 - rect.h/2;
	frect.w = rect.w*.75;
	frect.h = rect.h*.75;
	creditButton = new SpriteObject(rect, frect);

	rect.x = 0;
	rect.y = 0;
	rect.w = 552;
	rect.h = 80;


	frect.x = 1280 * .85 - rect.w / 2;
	frect.y = 720 * .85 - rect.h / 2;
	frect.w = rect.w * .75;
	frect.h = rect.h * .75;
	startButton = new SpriteObject(rect, frect);

	rect.x = 0;
	rect.y = 0;
	rect.w = 792;
	rect.h = 96;


	frect.x = 1280 * .6 - rect.w/2;
	frect.y = 720 * .15 - rect.h / 2;
	frect.w = rect.w * .75;
	frect.h = rect.h * .75;
	m_Name = new SpriteObject(rect, frect);




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

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("background"),m_backGround->GetSourceTransform(), m_backGround->GetDestinationFTransform());
	
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("credit"),creditButton->GetSourceTransform(), creditButton->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("game"),startButton->GetSourceTransform(), startButton->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("name"), m_Name->GetSourceTransform(), m_Name->GetDestinationFTransform());
}

void MenuState::Exit()
{
	std::cout << "Exiting Menu Screen" << std::endl;
	delete m_backGround;
	delete m_Name;
	delete startButton;
	delete creditButton;

	m_backGround = nullptr;
	m_Name = nullptr;
	startButton = nullptr;
	creditButton = nullptr;
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
	
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 720;


	frect.x = 0;
	frect.y = 0;
	frect.w = 1280;
	frect.h = 720;

	m_background = new SpriteObject(rect, frect);

	rect.x = 0;
	rect.y = 0;
	rect.w = 256;
	rect.h = 79;


	frect.x = 1280*.5 - (rect.w/2);
	frect.y = 720*.10 - (rect.h/2);
	frect.w = rect.w;
	frect.h = rect.h;
	m_title = new SpriteObject(rect, frect);

	rect.x = 0;
	rect.y = 0;
	rect.w = 256;
	rect.h = 79;


	frect.x = 1280 * .5 - (rect.w / 2);
	frect.y = 720 * .20 - (rect.h / 2);
	frect.w = rect.w;
	frect.h = rect.h;
	m_name = new SpriteObject(rect, frect);

	rect.x = 0;
	rect.y = 0;
	rect.w = 719;
	rect.h = 96;


	frect.x = 1280 * .5 - (rect.w / 2);
	frect.y = 720 * .88 - (rect.h / 2);
	frect.w = rect.w;
	frect.h = rect.h;
	m_button = new SpriteObject(rect, frect);

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

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("background"), m_background->GetSourceTransform(), m_background->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("creditTitle"), m_title->GetSourceTransform(), m_title->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("quincy"), m_name->GetSourceTransform(), m_name->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("menuButton"), m_button->GetSourceTransform(), m_button->GetDestinationFTransform());


}

void CreditState::Exit()
{
	std::cout << "Exiting Credit State" << std::endl;
	delete m_background;
	delete m_button;
	delete m_name;
	delete m_title;

	m_background = nullptr;
	m_button = nullptr;
	m_name = nullptr;
	m_title = nullptr;
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


	SDL_QueryTexture(TextureManager::Load("assets/real/background.png","background"), NULL, NULL, &rect.w,&rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 720 ;

	frect.x = 0;
	frect.y = 0;
	frect.w = 1280;
	frect.h = 720;

	m_background = new SpriteObject(rect, frect);


	SDL_QueryTexture(TextureManager::GetTexture("winTitle"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w;
	rect.h;

	frect.x = 1280*.5 - (rect.w/2);
	frect.y = 720*.15;
	frect.w = rect.w;
	frect.h = rect.h;

	m_title = new SpriteObject(rect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("restartButton"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w;
	rect.h;

	frect.x = 1280 *.5 - (rect.w/2);
	frect.y = 720*.85;
	frect.w = rect.w;
	frect.h = rect.h;

	m_button = new SpriteObject(rect, frect);
	
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
	
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("background"), m_background->GetSourceTransform(), m_background->GetDestinationFTransform());

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("winTitle"), m_title->GetSourceTransform(), m_title->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("restartButton"), m_button->GetSourceTransform(), m_button->GetDestinationFTransform());
}

void WinState::Exit()
{
	std::cout << "Exiting Win State" << std::endl;

	delete m_background;
	delete m_button;
	delete m_title;

	m_background = nullptr;
	m_button = nullptr;
	m_title = nullptr;
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


	SDL_QueryTexture(TextureManager::Load("assets/real/background.png", "background"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 720;

	frect.x = 0;
	frect.y = 0;
	frect.w = 1280;
	frect.h = 720;

	m_background = new SpriteObject(rect, frect);


	SDL_QueryTexture(TextureManager::GetTexture("lossTitle"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w;
	rect.h;

	frect.x = 1280 * .5 - (rect.w / 2);
	frect.y = 720 * .15;
	frect.w = rect.w;
	frect.h = rect.h;

	m_title = new SpriteObject(rect, frect);

	SDL_QueryTexture(TextureManager::GetTexture("restartButton"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
	rect.w;
	rect.h;

	frect.x = 1280 * .5 - (rect.w / 2);
	frect.y = 720 * .85;
	frect.w = rect.w;
	frect.h = rect.h;

	m_button = new SpriteObject(rect, frect);

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

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("background"), m_background->GetSourceTransform(), m_background->GetDestinationFTransform());

	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("lossTitle"), m_title->GetSourceTransform(), m_title->GetDestinationFTransform());
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("restartButton"), m_button->GetSourceTransform(), m_button->GetDestinationFTransform());
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState" << std::endl;
	delete m_background;
	delete m_button;
	delete m_title;

	m_background = nullptr;
	m_button = nullptr;
	m_title = nullptr;

	m_pMUS = Mix_LoadMUS("assets/Caketown1.mp3");
	Mix_VolumeMusic(40);
	Mix_PlayMusic(m_pMUS, -1);

}

void LoseState::Resume()
{
	std::cout << "Resuming Lose State" << std::endl;
}