#pragma once
#include "SDL.h"


class Sprite
{

public:
	Sprite();
	Sprite(SDL_Rect source, SDL_FRect Dest, int angle);


	SDL_Rect& GetSourceTransform() { return m_sourceTransform; }
	SDL_FRect& GetDestinationTransform() { return m_destinationTransform; }

	double GetAngle() { return m_angle; }

protected:
	SDL_Rect m_sourceTransform;
	SDL_FRect m_destinationTransform;

	int m_angle;


private:


};

