#pragma once
#include "SpriteObject.h"

class AnimatedSprite
	: public SpriteObject
{
public:
	AnimatedSprite(int angle, float frameTime, int maxSprites, SDL_Rect source, SDL_FRect destination)
		:SpriteObject(source, destination),
		m_currentSpriteIndex(0),
		m_maxSprites{ maxSprites },
		m_currentTime{ 0 },
		m_frameRate{frameTime}
	{}

	void Animate(float deltaTime);
protected:
	int m_currentSpriteIndex;
	int m_maxSprites;
	float m_currentTime;
	float m_frameRate;
};

