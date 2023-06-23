#pragma once
#include "SpriteObject.h"
#include "TextureManager.h"
class Bullet :
    public SpriteObject
{
public:
    Bullet(SDL_Rect source, SDL_FRect dest, const char* textureKey)
        :SpriteObject(source, dest, textureKey)
    {

    }
    Bullet(Bullet* other)
        :SpriteObject(other->m_sourceTransform,other->m_destinationTransform,other->textureKey)
    {
    }

    void SetVelocity(SDL_FPoint velo) { velocity = velo; }

    SDL_FPoint velocity = { 0,-600 };

};

