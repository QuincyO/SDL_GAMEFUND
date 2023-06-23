#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "SDL_image.h"
#include "SDL_mixer.h"

class SpriteObject;
class GameObject;
class AnimatedSprite;
class TiledLevel;
class Bullet;
class Ship;

class State
{
public:

	State() = default;
	virtual ~State() = default;

	virtual void Enter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Pause() {};
	virtual void Resume() {}

	std::unordered_map<std::string, GameObject*> m_objects;
protected:
};

class TitleState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Pause() {};
	virtual void Resume() {};

	float timer;
private:
	Mix_Chunk* m_pMix;
	Mix_Music* m_pMUS;
};


class GameState : public State
{
private:
	static const int kPlayerSpeed = 500;

	float enemySpawnTimer = 0;
	float enemySpawnDelay = 1.5f;
	Ship* playerShip;
	std::vector<GameObject*> m_backgroundObjects;
	std::vector<Ship*> EnemyShips;
	std::vector<Bullet*> EnemyBullets;
	std::vector<Bullet*> PlayerBullets;

	void DetectCollision();

	void SpawnShip();
	bool CanSpawn();


public:
	Mix_Music* gameMusic;
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
	virtual void Pause() override {};
};


class PauseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
private:
	//Pause Box
	SDL_Rect rect = { 1280/2 - (512/2),128,512,512};
};


class WinState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;

	Mix_Music* m_pMUS;
private:
	SpriteObject* m_background;
	SpriteObject* m_button;
	SpriteObject* m_title;
};

class LoseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override {};
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
	Mix_Music* m_pMUS;
private:

};