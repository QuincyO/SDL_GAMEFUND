#include "AnimatedSprite.h"
#include "Game.h"



AnimatedSprite::AnimatedSprite(SDL_Rect source, SDL_FRect dest)
    :SpriteObject(source,dest)
    , m_currentSpriteIndex(0),
    m_maxSprites{ 0 },
    m_startingSpriteIndex{ 0 },
    m_currentTime{ 0},
    m_frameRate{ 0 }
{
}



void AnimatedSprite::SetAnimation(float frameRate, int startingSpriteIndex, int totalSprites, int sourceY)
{
    m_currentTime = 0;
    m_frameRate = frameRate;
    m_currentSpriteIndex = 0;
    m_startingSpriteIndex = startingSpriteIndex;
    m_maxSprites = totalSprites;
    m_sourceTransform.x = m_sourceTransform.w * startingSpriteIndex;
    m_sourceTransform.y = sourceY;


}


void AnimatedSprite::Update(float deltaTime)
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



void Animated_Image::Update(float deltaTime)
{
    m_destinationTransform.y += scrollSpeed * deltaTime;
    if (m_destinationTransform.y >= Game::GetInstance().kHeight)
    {
        m_destinationTransform.y = -m_destinationTransform.h;
        NextFrame();
    }
}

void Animated_Image::Render()
{
    SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(textureKey), &m_sourceTransform, &m_destinationTransform, 0, 0, SDL_FLIP_NONE);
}

void Animated_Image::NextFrame()
{
    SetFrame(m_currentSpriteIndex + 1);
}

void Animated_Image::SetFrame(int frame)
{
    m_currentSpriteIndex = frame % m_maxSprites;
    int row = frame / 8;
    int col = frame % 8;

    m_sourceTransform.y = row * m_sourceTransform.h;
    m_sourceTransform.x = col * m_sourceTransform.w;
}
