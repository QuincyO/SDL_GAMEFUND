#pragma once
#include "SpriteObject.h"
class TileObject :
    public SpriteObject
{
public:
    TileObject(SDL_Rect source,SDL_FRect destination,bool obstacle,bool hazard)
        :SpriteObject(source,destination),
        m_obstacle{ obstacle },
        m_hazard{ hazard }
    {}

    TileObject* Clone()
    {
        return new TileObject(m_sourceTransform, m_destinationTransform, m_obstacle, m_hazard);
    }

    bool IsObstacle() { return m_obstacle; }
    void SetXY(float x, float y) { m_destinationTransform.x = x, m_destinationTransform.y = y; }
    void Update(float deltaTime) override {}
    void Render() override {}


private:
    bool m_obstacle;
    bool m_hazard;
};

