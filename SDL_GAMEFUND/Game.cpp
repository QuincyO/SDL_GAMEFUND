#include "Game.h"
#include "SoundManager.h"


Game::Game()
	:p_Renderer {nullptr}
	,p_Window{nullptr}
	,m_running{false}
	,SCREEN_HEIGHT{ kHeight }
	,SCREEN_WIDTH{ kWidth }
	,m_keyStates{ nullptr }
{

}

Game& Game::GetInstance()
{
	static Game* pInstance = new Game();
	return *pInstance;
}

int Game::Init(const char* Title)
{
	std::cout << "Initializing Engine..." << std::endl;

	//Initialize SDL and check if everything loaded correctly
	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (errorCode == 0)
	{
		std::cout << "SDL_Init Succeeded" << std::endl;
	}
	else
	{
		std::cout << "SDL_INIT() failed :" << errorCode << " : " << SDL_GetError() << std::endl;
		return 1;
	}
	
	p_Window = SDL_CreateWindow("Quincys Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (p_Window != NULL)
	{
		std::cout << "Window Created Successfully" << std::endl;
	}
	else
	{
		std::cout << "Window Failed to Create. Error Code"<<SDL_GetError() << std::endl;
		return 2;
	}

	p_Renderer = SDL_CreateRenderer(p_Window, -1, 0);

	if (p_Renderer != NULL)
	{
		std::cout << "Renderer Created Successfully" << std::endl;
	}
	else
	{
		std::cout << "Renderer Failed to Load. Error Code: " << SDL_GetError() << std::endl;
		return 3;
	}
	if (SoundManager::Init())
	{
		cout << "Sound Manager Init Good!" << endl;

	}
	else Game::Quit();

	EventManager::Init();
	StateManager::PushState(new TitleState());
	m_keyStates = SDL_GetKeyboardState(nullptr);
	m_running = true;
	return 0;


}
SDL_Renderer* Game::GetRenderer()
{
	return p_Renderer;
}


bool Game::IsRunning()
{
	return m_running;
}

void Game::Quit()
{
	m_running = false;
}

void Game::HandleEvents()
{
	EventManager::HandleEvents();
}

void Game::Update(float deltaTime)
{

	StateManager::Update(deltaTime);

}
void Game::Render()
{


	StateManager::Render();


	SDL_RenderPresent(p_Renderer);
}

void Game::Clean()
{
	std::cout << "Cleaning Engine..." << std::endl;
	TextureManager::Quit();
	StateManager::Quit();
	EventManager::Quit();
	SDL_DestroyRenderer(p_Renderer);
	SDL_DestroyWindow(p_Window);
	SDL_Quit();


	delete this;
}