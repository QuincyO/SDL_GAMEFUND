#pragma once
#include "SpriteObject.h"

class AnimatedSprite
	: public SpriteObject
{
public:
	virtual void Render() = 0;

protected:
	AnimatedSprite(SDL_Rect source, SDL_FRect dest);


	void SetAnimation(float frameRate, int startingSpriteIndex, int totalSprites, int sourceY = 0);
	virtual void Update(float deltaTime) override;
protected:
	int m_currentSpriteIndex;
	int m_startingSpriteIndex;
	int m_maxSprites;

	float m_currentTime;
	float m_frameRate;
};

