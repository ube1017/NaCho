#include "Player.h"
#include "KeyManager.h"
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "Missile.h"

HRESULT Player::Init()
{
	
	imageinfo.imageName = "Player";
	this->pos = { 640.0f ,100.0f };
	this->size = { 123,141 };
	this->hitBoxSize = { 20,20 };
	imageinfo.DrawRectSetting("Player", this->pos, { 123,141 });
	idleTimer.timerName = "플레이어 아이들 애니메이션타이머";
	TimerManager::GetSingleton()->SetTimer(idleTimer,this,&Player::Idle , 0.035f);
	TimerManager::GetSingleton()->SetTimer(fireTimer, this, &Player::FireDelay, 0.10f);
	isFire = true;
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
	hitBox = {	(LONG)pos.x - hitBoxSize.cx/2 -3, (LONG)pos.y - hitBoxSize.cy - 4,
				(LONG)pos.x + hitBoxSize.cx/2 -3, (LONG)pos.y - 4 };

	
}

void Player::Render(HDC hdc)
{
	Character::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
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
	if (isFire)
	{
		Missile* missile;
		FPOINT missilePos = this->pos;
		missilePos.x += 5.0f;
		missilePos.y -= 20.0f;
		PlayScene* playscene = Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missileManager = playscene->GetMissileManager();
		for (int i = 0; i < 3; i++)
		{
			missilePos.x -= (5.0f * i);
			missile = missileManager->SpawnPlayerMissile(this, "21", missilePos, { 20,20 });
			missile->SetSpeed(-3.0f);
			missile->SetMovePatten(Patten::NORMALMOVE);
		}
		isFire = false;
	}
}

void Player::FireDelay()
{
	isFire = true;
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
