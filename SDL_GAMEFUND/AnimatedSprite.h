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

class Animated_Image : public AnimatedSprite
{
public:
	Animated_Image(SDL_Rect source, SDL_FRect dest, const char* textureKey, float scrollSpeed = 0, int frameCount = 0)
		:AnimatedSprite(source, dest),
		textureKey{ textureKey },
		scrollSpeed{ scrollSpeed }
	{
		m_maxSprites = frameCount;
	}
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void NextFrame();
	void SetFrame(int frame);


private:
	const char* textureKey;
	float scrollSpeed;
};