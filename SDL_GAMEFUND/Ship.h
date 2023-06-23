#pragma once
#include "SpriteObject.h"
#include <vector>

class Bullet;

    enum class ShipType
    {
        FRIEND,
        ENEMY
    };
class Ship :
    public SpriteObject
{
private:
    float moveSpeed;
    bool shooting;
    float fireDelay;



    enum class ShipState
    {
        STATE_NORM,
        STATE_LEFT,
        STATE_RIGHT
    };

    float shootTimer;
    ShipState m_state;

    ShipType m_ShipType;


public:
    Ship(SDL_Rect source, SDL_FRect dest, const char* textureKey, ShipType shiptype, float moveSpeedPx = 150, float fireDelay = 0.3f)
        :SpriteObject(source, dest, textureKey),
        moveSpeed{ moveSpeedPx },
        fireDelay{ fireDelay },
        m_state{ ShipState::STATE_NORM },
        m_ShipType{ shiptype },
        shooting{ false },
        shootTimer{ 0 }

    {

    }
    Ship(Ship* other)
        :SpriteObject(other->m_sourceTransform, other->m_destinationTransform, other->textureKey),
        moveSpeed{ other->moveSpeed },
        shooting{ other->shooting },
        fireDelay{ other->fireDelay },
        m_state{ other->m_state },
        m_ShipType{ other->m_ShipType },
        shootTimer{ other->shootTimer }
    {

    }


    ~Ship() {

    }
    void Shoot(std::vector<Bullet*>& container);

    virtual void Render()override;

    virtual void Update(float deltaTime, std::vector<Bullet*>& containerOfBullets);

    bool canShoot() { if (shootTimer <= 0.0f && m_destinationTransform.y>= 0) return true; else return false; }






};

