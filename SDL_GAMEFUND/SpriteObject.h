#pragma once
#include "GameObject.h"
#include <SDL.h>
class SpriteObject : public GameObject
{
public:
    SpriteObject(const SDL_Rect source, const SDL_FRect dest)
        :GameObject(dest),
        m_sourceTransform{source}
    {   }

    SDL_Rect* GetSourceTransform() { return &m_sourceTransform; }
   


protected:
    SDL_Rect m_sourceTransform;

};

