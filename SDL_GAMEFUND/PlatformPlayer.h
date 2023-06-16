#pragma once
#include "AnimatedSprite.h"



class PlatformPlayer :
    public AnimatedSprite
{
private:
    enum class PlayerState { kIdle, kRunning, kJumping, kDying };
    bool m_grounded;
    bool m_facingLeft;
    float m_accelX;
    float m_accelY;
    float m_velX;
    float m_velY;

    PlayerState m_states;

    static const float s_kAccelerationX;
    static const float s_kGravity;
    static const float s_kJumpForce;
    static const float s_kMaxVelocityX;
    static const float s_kMaxVelocityY;
    static const float s_kDragX;

public:
    PlatformPlayer(SDL_Rect sourceTransform, SDL_FRect destTransform);
    ~PlatformPlayer();
    virtual void Update(float deltaTIme);
    virtual void Render();
    void Jump();
    void Stop();

    void StopX() { m_velX = 0.0f; }
    void StopY() { m_velY = 0.0f; }
    void SetAccelX(float x) { m_accelX = x; }
    void SetAccelY(float y) { m_accelY = y; }
    bool IsGrounded() { return m_grounded; }
    void SetGrounded(bool g) { m_grounded = g; }
    float GetVelX() { return m_velX; }
    float GetVelY() { return m_velY; }
    void SetX(float x) { m_destinationTransform.x = x; }
    void SetY(float y) { m_destinationTransform.y = y; }
};

