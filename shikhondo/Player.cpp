#include "Player.h"
#include "KeyManager.h"

HRESULT Player::Init()
{
	return E_NOTIMPL;
}

void Player::Release()
{
}

void Player::Update()
{
	this->KeyChack();
}

void Player::Render(HDC hdc)
{
}


void Player::KeyChack()
{
	KeyManager* keyManager = KeyManager::GetSingleton();
	if (keyManager)
	{
		if (keyManager->IsStayKeyDown(VK_RIGHT))
		{
			pos.x += speed;
		}
		else if (keyManager->IsStayKeyDown(VK_LEFT))
		{
			pos.x -= speed;
		}

		if (keyManager->IsStayKeyDown(VK_UP))
		{
			pos.y -= speed;
		}
		else if (keyManager->IsStayKeyDown(VK_DOWN))
		{
			pos.y += speed;
		}


		if (keyManager->IsStayKeyDown(ZKey))
			this->Fire();
		if (keyManager->IsOnceKeyDown(XKey))
			this->SlowMove();
		else if (keyManager->IsOnceKeyUp(XKey))
			this->SlowMove();
		if (keyManager->IsOnceKeyDown(CKey))
			this->Boom();
	}
}

void Player::Fire()
{
}

void Player::SlowMove()
{
	if (moveState == MoveState::NORMAL)
	{
		moveState = MoveState::SLOW;
		speed = 1.0f;
	}
	else
	{
		moveState = MoveState::NORMAL;
		speed = 3.0f;
	}
}

void Player::Boom()
{
}
