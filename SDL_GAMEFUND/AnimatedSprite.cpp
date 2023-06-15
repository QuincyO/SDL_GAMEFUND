#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Rect source, SDL_FRect dest)
    :SpriteObject(source,dest)
    , m_currentSpriteIndex(0),
    m_maxSprites{ 0 },
    m_currentTime{ 0},
    m_frameRate{ 0 }
{
}

void AnimatedSprite::SetAnimation(int angle, float frameTIme, int maxSrite)
{
    m_angle = angle;
    m_frameRate = frameTIme;
    m_maxSprites = maxSrite;
}

void AnimatedSprite::Animate(float deltaTime)
{
    m_currentTime += deltaTime;

    if (m_currentTime > m_frameRate)
    {
        m_currentTime = m_frameRate - m_currentTime;
        m_currentSpriteIndex++;

        if (m_currentSpriteIndex == m_maxSprites)
        {
            m_currentSpriteIndex = 0;
        }
    }

    m_sourceTransform.x = m_sourceTransform.w * m_currentSpriteIndex; //this line updates the x pos to go over to the next one
}

void AnimatedSprite::Update(float deltaTime)
{
    Animate(deltaTime);
}
