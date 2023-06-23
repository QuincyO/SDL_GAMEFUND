#include "SpriteObject.h"
#include "Game.h"

void Static_Image::Render()
{

		SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform
			, 0, 0, SDL_FLIP_NONE);
	

}
