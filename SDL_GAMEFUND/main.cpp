#define SDL_MAIN_HANDLED
#include <iostream>
#include "Game.h"
#include <chrono>
#include "vld.h"

int main(int argc, char* argv[])
{
	SDL_SetMainReady();
	Game& myGame = Game::GetInstance();
	int result = myGame.Init("Quincy's Box");
	if (result == 0)
	{
		//Allocate a time_point outside that loop so that it is retained between frames
		auto LastFrameTime = std::chrono::high_resolution_clock::now();


		while (myGame.IsRunning())
		{
			//Get current time_point
			auto ThisFrameTime = std::chrono::high_resolution_clock::now();

			//Subtract last frames time_point from this frames time_point to get the duration of the frame
			std::chrono::duration<float> LastFrameDuration = ThisFrameTime - LastFrameTime;

			//Convert the duration to a float
			float deltaTime = LastFrameDuration.count();

			//Passing the newframe counter to the last frame counter
			LastFrameTime = ThisFrameTime;


			myGame.HandleEvents();
			myGame.Update(deltaTime);
			myGame.Render();

		}
	}
	myGame.Clean();

	return 0;
}