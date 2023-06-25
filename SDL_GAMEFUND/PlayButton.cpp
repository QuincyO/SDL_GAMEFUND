#include "PlayButton.h"
#include "StateManager.h"
#include "EventManager.h"
#include "state.h"

PlayButton::PlayButton(SDL_Rect source, SDL_FRect destination, const char* textureKey,const char* buttonText)
	:UI_Button(source,destination,textureKey, buttonText)
{
	TextureManager::LoadString(buttonText, "PlayText");
}



void PlayButton::Execute()
{
	EventManager::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
	StateManager::ChangeState(new GameState());
}