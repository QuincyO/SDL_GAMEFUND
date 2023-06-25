#pragma once
#include "UI_Button.h"
class ResumeButton :
    public UI_Button
{
    public:
        ResumeButton(SDL_Rect source, SDL_FRect dest, const char* textureKey,const char* buttonText);

    virtual void Execute() override;


private:
};

