#pragma once
#include "SpriteObject.h"
#include "SoundManager.h"
#include <string>
#include <SDL.h>


class UI_Button :
    public SpriteObject
{
public:
    UI_Button(SDL_Rect source, SDL_FRect  destination, const char* textureKey);
    virtual void Update(float deltaTime) override;
    virtual void Render() override;

protected:

    enum class ButtonState
    {
        STATE_UP,
        STATE_DOWN,
        STATE_OVER,
        COUNT
    };

    ButtonState m_state;

    virtual void Execute() = 0;
};

