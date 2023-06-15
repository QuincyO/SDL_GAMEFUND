#include "SpriteObject.h"

SpriteObject::SpriteObject()
	:m_sourceTransform{0,0,0,0}
	,m_destinationTransform{0,0,0,0}
	,m_angle(0)
{
	
}

SpriteObject::SpriteObject(SDL_Rect source, SDL_FRect dest, int angle)
	:m_sourceTransform{source}
	,m_destinationTransform{dest}
	,m_angle{angle}
{
}
