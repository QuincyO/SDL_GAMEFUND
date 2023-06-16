#include "PlatformPlayer.h"
#include "Game.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "AnimatedSprite.h"
#include "SoundManager.h"
#include <cmath>

const float PlatformPlayer::s_kAccelerationX = 250;
const float PlatformPlayer::s_kGravity = 50;
const float PlatformPlayer::s_kJumpForce = 2500;
const float PlatformPlayer::s_kMaxVelocityX = 350;
const float PlatformPlayer::s_kMaxVelocityY = 2000;
const float PlatformPlayer::s_kDragX = 0.8f;

PlatformPlayer::PlatformPlayer(SDL_Rect sourceTransform, SDL_FRect destTransform)
	:AnimatedSprite(sourceTransform,destTransform),
	m_grounded{ false },
	m_facingLeft{false},
	m_accelX{0},
	m_accelY{ 0 },
	m_velX{ 0 },
	m_velY{ 0 },
	m_states{PlayerState::kIdle}
{
	SetAnimation(0.1f, 0, 1, 256);
	SoundManager::LoadSound("assets/Sound/Effects/jump.wav", "Jump");
	SoundManager::LoadSound("assets/Sound/Effects/land.wav", "Land");
}

PlatformPlayer::~PlatformPlayer()
{
	SoundManager::UnloadSound("Jump");
	SoundManager::UnloadSound("Land");
}

void PlatformPlayer::Update(float deltaTime)
{
	switch (m_states)
	{
	case PlayerState::kIdle:
		//Transition to run
		if (EventManager::KeyPressed(SDL_SCANCODE_A) || EventManager::KeyPressed(SDL_SCANCODE_D))
		{
			m_states = PlayerState::kRunning;
			 SetAnimation(0.1f, 0, 8, 256);
		}
		else if (EventManager::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			Jump();
		}
		break;
	case PlayerState::kRunning:
		//Moving Left or Right
		if (EventManager::KeyHeld(SDL_SCANCODE_A) && m_destinationTransform.x > 0)
		{
			m_accelX = -s_kAccelerationX;
			if (!m_facingLeft)
			{
				m_facingLeft = true;
			}
		}
		else if (EventManager::KeyHeld(SDL_SCANCODE_D) && m_destinationTransform.x < Game::kWidth - m_destinationTransform.w)
		{
			m_accelX = s_kAccelerationX;
			if (m_facingLeft) m_facingLeft = false;
		}

		//Transition to jump
		if (EventManager::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			Jump();
		}

		//Transition to Idle

		if (!EventManager::KeyHeld(SDL_SCANCODE_A) && !EventManager::KeyHeld(SDL_SCANCODE_D))
		{
			m_states = PlayerState::kIdle;
			SetAnimation(0.1f,0,1,256);
		}
		break;
	case PlayerState::kJumping:
		if (EventManager::KeyHeld(SDL_SCANCODE_A) && m_destinationTransform.x > 0)
		{
			m_accelX = -s_kAccelerationX;
			if (!m_facingLeft) m_facingLeft = true;
		}
		else if (EventManager::KeyHeld(SDL_SCANCODE_D) && m_destinationTransform.x < Game::kWidth - m_destinationTransform.w)
		{
			m_accelX = s_kAccelerationX;
			if (m_facingLeft) m_facingLeft = false;
		}

		//Hit the ground, transition to run
		if (m_grounded)
		{
			SoundManager::PlaySound("Land");
			m_states = PlayerState::kRunning;
			SetAnimation(0.1f,0,8,256);
			
		}
	}

	//Player Movement X Axis First
	m_velX += m_accelX;
	m_velX *= (m_grounded ? s_kDragX : 1.0f);
	m_velX = std::min(std::max(m_velX, -s_kMaxVelocityX), s_kMaxVelocityX);
	m_destinationTransform.x += m_velX * deltaTime;

	//Player Movement Y Axis Second
	m_velY += m_accelY + s_kGravity;
	m_velY = std::min(std::max(m_velY, -s_kMaxVelocityY), s_kMaxVelocityY);

	m_destinationTransform.y += m_velY * deltaTime;

	//Resetting Accel Every Frame
	m_accelX = 0.0f;
	m_accelY = 0.0f;

	AnimatedSprite::Update(deltaTime);

}


void PlatformPlayer::Render()
{
	SDL_RenderCopyExF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture("player"),
		&m_sourceTransform, &m_destinationTransform, 0.0, nullptr, (m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));

}

void PlatformPlayer::Jump()
{
	SoundManager::PlaySound("Jump");
	m_accelY = -s_kJumpForce;
	m_grounded = false;
	m_states = PlayerState::kJumping;
	SetAnimation(0.1f,8,1,256);
}

void PlatformPlayer::Stop()
{
	StopX();
	StopY();
}