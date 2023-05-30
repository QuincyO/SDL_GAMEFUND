#pragma once
#include <SDL.h>

class GameObject
{
public:
	GameObject()
		:m_destinationTransform({ 0,0,0,0 })
	{}

	GameObject(const SDL_FRect destination)
		:m_destinationFTransform(destination)
	{
		m_destinationTransform = {
			(int)m_destinationFTransform.x,
			(int)m_destinationFTransform.y,
			(int)m_destinationFTransform.w,
			(int)m_destinationFTransform.h,
		};
	}
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	SDL_FRect* GetDestinationFTransform() { return &m_destinationFTransform; }

	SDL_Rect* GetDestinationTransform() { return &m_destinationTransform; }


protected:
	SDL_Rect m_destinationTransform;
	SDL_FRect m_destinationFTransform;
};