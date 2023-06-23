#include "Ship.h"
#include <iostream>
#include "Bullet.h"
#include "Game.h"
#include "SoundManager.h"

void Ship::Shoot(std::vector<Bullet*>& container)
{
	Bullet* tempBullet = nullptr;
	SDL_Rect source;
	SDL_FRect dest;
	source.x = 0;
	source.y = 0;
	source.w = 9;
	source.h = 33;

	dest.x = m_destinationTransform.x + (m_destinationTransform.w / 2) - (source.w / 2);
	dest.y = m_destinationTransform.y;

	dest.w = source.w * .75f;
	dest.h = source.h * .75f;

	if (m_ShipType == ShipType::FRIEND)
	{
		const char* FriendlyTextureKey = "PlayerLaser";
		tempBullet = new Bullet(source, dest, FriendlyTextureKey);
		container.push_back(new Bullet(tempBullet));
		SoundManager::PlaySound("ShootFX1");
	}
	else if (m_ShipType == ShipType::ENEMY)
	{
		const char* EnemyTextureKey = "EnemyLaser";

		tempBullet = new Bullet(source, dest, EnemyTextureKey);
		tempBullet->SetVelocity({ 0,200 });
		container.push_back(new Bullet(tempBullet));
		SoundManager::PlaySound("ShootFX3");
	}
	else std::cout << "Unable To Create Bullets" << std::endl;
	shootTimer = fireDelay;

	delete tempBullet;
	tempBullet = nullptr;
}

void Ship::Render()
{
	m_sourceTransform.x = m_sourceTransform.w * (int)m_state;
	SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform, 0, 0, SDL_FLIP_NONE);
}

void Ship::Update(float deltaTime,std::vector<Bullet*>& containerOfBullets)
{
	if (m_ShipType == ShipType::ENEMY)
	{
		m_destinationTransform.y += moveSpeed * deltaTime;
		if (canShoot())
		{
			Shoot(containerOfBullets);
		}
	}
	else {


		m_state = ShipState::STATE_NORM;
		if (EventManager::KeyHeld(SDL_SCANCODE_A))
		{
			m_destinationTransform.x -= moveSpeed * deltaTime;
		}
		if (EventManager::KeyHeld(SDL_SCANCODE_D))
		{
			m_destinationTransform.x += moveSpeed * deltaTime;
		}
		if (EventManager::KeyHeld(SDL_SCANCODE_W)) m_destinationTransform.y -= moveSpeed * deltaTime;
		if (EventManager::KeyHeld(SDL_SCANCODE_S)) m_destinationTransform.y += moveSpeed * deltaTime;
		if (EventManager::KeyHeld(SDL_SCANCODE_SPACE)) shooting = true;
		else shooting = false;



		if (m_destinationTransform.x >= Game::GetInstance().kWidth)
		{
			m_destinationTransform.x = 0 - m_destinationTransform.w;
		}
		if (m_destinationTransform.x <= -m_destinationTransform.w - 1)
		{
			m_destinationTransform.x = Game::kWidth;
		}
		if (m_destinationTransform.y >= Game::kHeight - m_destinationTransform.h - 10)
		{
			m_destinationTransform.y = Game::kHeight - m_destinationTransform.h - 11;
		}
		if (m_destinationTransform.y <= 0 + 10)
		{
			m_destinationTransform.y = 10;
		}
		if (shooting && canShoot())
		{
			Shoot(containerOfBullets);
		}
	}







	shootTimer -= deltaTime;
}