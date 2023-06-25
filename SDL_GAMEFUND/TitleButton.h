#pragma once
#include "UI_Button.h"
class TitleButton :
    public UI_Button
{
public:
    TitleButton(SDL_Rect source,SDL_FRect dest,const char* textureKey,const char* TEXT)
        :UI_Button(source,dest,textureKey,TEXT)
    {}

     void Execute();

};

