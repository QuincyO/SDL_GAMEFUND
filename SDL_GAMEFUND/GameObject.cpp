#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height, Uint8 r  , Uint8 g  , Uint8 b, Uint8 a )
	:m_transform{x,y,width,height},
	m_color{r,g,b,a}


{

}

void GameObject::Draw(SDL_Renderer* pRen)
{
	SDL_SetRenderDrawColor(pRen, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRectF(pRen, &m_transform);
}

void GameObject::UpdatePositionX(float x)
{
	m_transform.x += x;

}


void GameObject::UpdatePositionY(float y)
{
	m_transform.y += y;

}