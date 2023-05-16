#include "Game.h"
Game::Game()
	:p_Renderer {nullptr}
	,p_Window{nullptr}
	,m_running{false}
	,SCREEN_HEIGHT{ 1024 }
	,SCREEN_WIDTH{896}
	,m_RectangleTransform{kWidth/2,kHeight/2,100,100}
	,m_keyStates{ nullptr }
{

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

	StateManager::PushState(new TitleState());
	m_keyStates = SDL_GetKeyboardState(nullptr);
	m_running = true;
	return 0;


}
SDL_Renderer* Game::GetRenderer()
{
	return p_Renderer;
}
Game& Game::GetInstance()
{
	static Game* pInstance = new Game();
	return *pInstance;
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;


		}
	}
}
bool Game::KeyDown(SDL_Scancode key)
{
	if (m_keyStates)
	{
		return m_keyStates[key] == 1;
	}
	return false;
}
void Game::Update(float deltaTime)
{

	StateManager::Update(deltaTime);
	//if (KeyDown((SDL_SCANCODE_W)))
	//{
	//	m_RectangleTransform.y -= kRectangleSpeed * deltaTime;
	//}
	//if (KeyDown((SDL_SCANCODE_S)))
	//{
	//	m_RectangleTransform.y+= kRectangleSpeed*deltaTime;
	//}
	//if (KeyDown((SDL_SCANCODE_A)))
	//{
	//	m_RectangleTransform.x-= kRectangleSpeed*deltaTime;
	//}
	//if (KeyDown((SDL_SCANCODE_D)))
	//{
	//	m_RectangleTransform.x += kRectangleSpeed * deltaTime;
	//}
}
void Game::Render()
{
	//  //Drawing Background and Clearing Renderer
	//  SDL_SetRenderDrawColor(p_Renderer, 0, 128, 255, 255);
	//  SDL_RenderClear(p_Renderer);
	//  
	//  
	//  //Drawing things
	//  SDL_SetRenderDrawColor(p_Renderer, 0, 0, 255, 255);
	//  SDL_RenderFillRectF(p_Renderer, &m_RectangleTransform);

	StateManager::Render();


	SDL_RenderPresent(p_Renderer);
}

void Game::Clean()
{
	std::cout << "Cleaning Engine..." << std::endl;
	SDL_DestroyRenderer(p_Renderer);
	SDL_DestroyWindow(p_Window);
	SDL_Quit();
	StateManager::Quit();

	delete this;
}