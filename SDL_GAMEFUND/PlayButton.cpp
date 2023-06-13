#include "PlayButton.h"
#include "StateManager.h"
#include "state.h"

PlayButton::PlayButton(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	:UI_Button(source,destination,textureKey)
{}

void PlayButton::Execute()
{
	StateManager::ChangeState(new GameState());
}