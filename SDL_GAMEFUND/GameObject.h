#pragma once
#include <SDL.h>

class GameObject
{
public:
	GameObject(float x,float y,float width,float height, Uint8 r =255 , Uint8 g =255, Uint8 b =255, Uint8 a=255);


	void Draw(SDL_Renderer* pRen);
	void UpdatePositionX(float x);
	void UpdatePositionY(float y);
	SDL_FRect& GetTransform() { return m_transform; };

private:
	float kSpeed = 500;
	SDL_Color m_color;
	SDL_FRect m_transform;
};