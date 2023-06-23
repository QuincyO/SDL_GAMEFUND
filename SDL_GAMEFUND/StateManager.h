#pragma once
#include <vector>
class State;

class StateManager
{
private:
	static std::vector<State*> s_states;
	static bool s_stateChange;
public:
	static void Update(float deltaTime);
	static void Render();
	static void PushState(State* pState); //Used when going to PauseState
	static void PopState(); //used when leaving pause State
	static void ChangeState(State* pState); //
	static void Quit();
	static std::vector<State*>& GetStates(); //Returns a reference to our State* vector

	static bool isStateChanging() { return s_stateChange; }

private:
	StateManager() {}
};