#include "Sprite.h"


Sprite::Sprite()
	:m_sourceTransform  {0,0,0,0},
	m_destinationTransform{0,0,0,0},
	m_angle{ 0 }

{}

Sprite::Sprite(SDL_Rect source, SDL_FRect Dest, int angle)
	:m_sourceTransform{ source },
	m_destinationTransform{ Dest },
	m_angle{angle}
{}