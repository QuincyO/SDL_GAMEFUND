#pragma once
#include <SDL.h>
#include <vector>

#include "SDL_image.h"
#include "SDL_mixer.h"

class SpriteObject;
class GameObject;
class AnimatedSprite;
class TiledLevel;

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
private:
	SpriteObject* m_spriteLogo;
};


class GameState : public State
{
private:
	static const int kPlayerSpeed = 500;
	TiledLevel* m_pLevel;

	Mix_Music* m_pMusic;



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