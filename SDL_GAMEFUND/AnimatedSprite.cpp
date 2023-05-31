#include "AnimatedSprite.h"



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