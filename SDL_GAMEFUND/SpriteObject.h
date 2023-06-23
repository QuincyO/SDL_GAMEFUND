#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <string>
class SpriteObject : public GameObject
{
public:
    SpriteObject(const SDL_Rect source, const SDL_FRect dest,const char* textureKey)
        :GameObject(dest),
        textureKey{ textureKey },
        m_sourceTransform{source}
    {   }

    SDL_Rect* GetSourceTransform() { return &m_sourceTransform; }
   
    void Update([[maybe_unused]] float deltaTime) override {}
    void Render() override {};

protected:
    SDL_Rect m_sourceTransform;
    const char* textureKey;
};

class Static_Image : public SpriteObject
{
public: 
    Static_Image(const SDL_Rect source, const SDL_FRect dest, const char* textureKey,float scrollSpeed = 0)
        :SpriteObject(source, dest, textureKey),
        scrollSpeed{scrollSpeed}
    {

    }
    virtual void Update([[maybe_unused]] float deltaTime) override;
    virtual void Render() override;

private:
    float scrollSpeed;

};