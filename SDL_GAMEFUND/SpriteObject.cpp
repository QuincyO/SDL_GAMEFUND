#include "SpriteObject.h"
#include "Game.h"

void Static_Image::Update(float deltaTime)
{
	m_destinationTransform.y += scrollSpeed * deltaTime;

	if (m_destinationTransform.y >= Game::GetInstance().kHeight)
	{
		m_destinationTransform.y = 0 - m_destinationTransform.h;
	}
}

void Static_Image::Render()
{

		SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform
			, 0, 0, SDL_FLIP_NONE);
	

}
