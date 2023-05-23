#pragma once
#include <vector>
#include "GameObject.h"
#include "SDL_image.h"
class GameObject;
class AnimatedSprite;

class State
{
public:

	State() = default;
	virtual ~State() = default;

	virtual void Enter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() {}
};

class TitleState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

	float timer;
};


class GameState : public State
{
	std::vector<AnimatedSprite*> m_gameObjects;
	GameObject* m_player;
	GameObject* killBox;
	float kPlayerSpeed = 500;
	float m_timer;
	SDL_Texture* m_playerTexture;
	SDL_Texture* m_objectTexture;

	//Mix_Music* m_pMusic;



public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};


class PauseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class MenuState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};

class CreditState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};

class WinState : public State
{
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};

class LoseState : public State
{
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};