#include "TitleButton.h"
#include "StateManager.h"
#include "state.h"

void TitleButton::Execute()
{
	StateManager::ChangeState(new TitleState);
}
