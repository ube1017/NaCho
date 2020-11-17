#include "Player.h"
#include "KeyManager.h"

HRESULT Player::Init()
{
	imageinfo.imageName = "Player";
	this->pos = { 640.0f ,100.0f };
	imageinfo.drwrc = { (LONG)pos.x - 61, (LONG)pos.y - 70, (LONG)pos.x + 62,(LONG)pos.y + 71 };
	TimerManager::GetSingleton()->SetTimer(idleTimer,this,&Player::Idle , 0.035f);
	speed = 3.0f;
	return S_OK;
}

void Player::Release()
{
	GameNode::Release();
}

void Player::Update()
{
	GameNode::Update();
	this->KeyChack();
}

void Player::Render(HDC hdc)
{
	Character::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
}


void Player::KeyChack()
{
	KeyManager* keyManager = KeyManager::GetSingleton();
	if (keyManager)
	{
		if (keyManager->IsStayKeyDown(VK_RIGHT))
		{
			if (pos.x + speed < Play_RightX)
			{
				imageinfo.MovePos(MovePosType::X_AIS, speed);
				pos.x += speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_LEFT))
		{
			if (pos.x - speed > Play_LeftX)
			{
				imageinfo.MovePos(MovePosType::X_AIS, -speed);
				pos.x -= speed;
			}
		}

		if (keyManager->IsStayKeyDown(VK_UP))
		{
			if (pos.y - speed > 0)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, -speed);
				pos.y -= speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_DOWN))
		{
			if (pos.y + speed < WINSIZE_Y)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, +speed);
				pos.y += speed;
			}
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

void Player::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 21)
		imageinfo.framex = 0;
}
