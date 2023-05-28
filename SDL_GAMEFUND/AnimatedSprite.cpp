#include "AnimatedSprite.h"




AnimatedSprite::AnimatedSprite(int angle, float frameRate, int maxSprite, SDL_Rect sourceTransform, SDL_FRect DestTransform)
	:Sprite(sourceTransform, DestTransform, angle),
	m_currentSpriteIndex{ 0 },
	m_maxSprites{ maxSprite },
	m_currentTime{ 0 },
	m_frameRate{ frameRate }
{}


void AnimatedSprite::Animate(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameRate)
	{
		m_currentTime = m_currentTime - m_frameRate;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_maxSprites)
		{
			m_currentSpriteIndex = 0;
		}
	}

	m_sourceTransform.x = m_sourceTransform.w * m_currentSpriteIndex;
}

