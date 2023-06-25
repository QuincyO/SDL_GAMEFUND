#include "ResumeButton.h"
#include "EventManager.h"
#include "StateManager.h"
#include "Game.h"

ResumeButton::ResumeButton(SDL_Rect source, SDL_FRect dest, const char* textureKey, const char* buttonText)
	:UI_Button(source,dest,textureKey, buttonText)
{
	TextureManager::LoadString(buttonText,"ResumeText");
}



void ResumeButton::Execute()
{
	StateManager::PopState();
	
}
