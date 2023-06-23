#include "Bullet.h"
#include "Game.h"
void Bullet::Update(float deltaTime)
{
	m_destinationTransform.x += velocity.x * deltaTime;
	m_destinationTransform.y += velocity.y * deltaTime;
}
void Bullet::Render()
{
	if (SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform, 0, 0, SDL_FLIP_NONE) == -1)
	{
	 std::cout << "Bullet Failed to Render - " << SDL_GetError() << std::endl;
	}
	
}
