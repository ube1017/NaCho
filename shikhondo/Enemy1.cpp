#include "Enemy1.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy1::Init()
{
	hp = 20;
	damge = 1;
	speed = 1.5f;
	missileSpeed = 2.0f;
	size.cx = 30;
	size.cy = 60;
	hitBoxSize = size;
	locationCount = 0;
	mapInCheck = false;
	mapOutCheck = false;
	angleCheck = false;
	pattenCheck = false;
	startCheck = false;
	EAngle = 0;
	checkTime = 0;
	leftCheck = 0;
	moveTime = 0;
	// 패턴 
	pattenX = 150;
	pattenY = 5;

	AutomaticMissile = false;
	
	imageinfo.DrawRectSetting("enemy1", this->pos, { 100,100 }, true, { 100,100 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy1::Idle, 0.070f);

	return E_NOTIMPL;
}

void Enemy1::Release()
{
}

void Enemy1::Update()
{
	if (!startCheck && !pattenCheck)
	{
		LocationReset();
		startCheck = true;
	}

	Enemy::Update();
	imageinfo.MovePos(pos);
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
				(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (!AutomaticMissile && checkTime >= 3.0f)
	{
		// 탄 발사전 좌표지정
		PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
		// 각도를 받고
		Missile* Em1 = playScene->SpawnMissile(this, "EnemyMissile", this->pos, { 30, 30 });

		Em1->SetAngle(this->GetAngle());		// 각도 값
		Em1->SetSpeed(missileSpeed);			// 총알 스피드
		Em1->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴

		AutomaticMissile = true;
		checkTime = 0;
	}
	else if (AutomaticMissile)
	{
		if (checkTime >= 1.0f)
		{
			checkTime = 0;
			AutomaticMissile = false;
		}
	}
	moveTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (moveTime >= 1.0f)
	{
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{
				if (!pattenCheck)
				{//그 각도로 움직이는 코드
					LocationReset();
					moveTime = 0;
				}
				else
				{
					monsterPatten2();
					moveTime = 0;
				}
			}
		}
	}
}

void Enemy1::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
#endif // _DEBUG
	//Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
}

void Enemy1::RandLocation()
{
	//RandPos.x = WINSIZE_X / 2 + 400;
	//RandPos.y = -100;

	//this->pos.x = RandPos.x;
	//this->pos.y = RandPos.y;
	imageinfo.MovePos(RandPos);
}

void Enemy1::LocationReset()
{
	locationCount++;
	monsterPatten(locationCount);
}

void Enemy1::Death()
{
	Character::Death();
	TimerManager::GetSingleton()->DeleteTimer(idleTimer);
}

void Enemy1::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 12)
	{
		imageinfo.framex = 0;
	}
}

void Enemy1::monsterPatten(int locationCount)
{
	if (leftCheck == 0)
	{
		if (pos.x > WINSIZE_X / 2)
		{
			leftCheck = 1;
		}
		else
		{
			leftCheck = 2;
		}
	}
	
	if (leftCheck == 1)
	{
		switch (locationCount)
		{
		case 1:
			RandPos.x = WINSIZE_X / 2 + 130;
			RandPos.y = 300 - 50;
			break;
		case 2:
			RandPos.x = WINSIZE_X / 2;
			RandPos.y = 300;
			break;
		case 3:
			RandPos.x = WINSIZE_X / 2 - 150;
			speed = 0.8f;
			break;
		case 4:
			switch (RandNum)
			{
			case 0:
				speed = 1.0f;
				RandPos.x = -100;
				RandPos.y = 150;
				break;
			case 1:
				speed = 1.0f;
				RandPos.x = -100;
				RandPos.y = 450;
				break;
			case 2:
				speed = 1.0f;
				RandPos.x = 200;
				RandPos.y = -100;
				break;
			case 3:
				speed = 1.0f;
				RandPos.x = WINSIZE_X + 200;
				RandPos.y = 500;
			default:
				break;
			}
			locationCount = 0;
			break;
		default:
			break;
		}
	}
	else if (leftCheck == 2)
	{
		switch (locationCount)
		{
		case 1:
			RandPos.x = WINSIZE_X / 2 - 130;
			RandPos.y = 300 - 50;
			break;
		case 2:
			RandPos.x = WINSIZE_X / 2;
			RandPos.y = 300;
			break;
		case 3:
			RandPos.x = WINSIZE_X / 2 + 150;
			speed = 0.8f;
			break;
		case 4:
			speed = 1.0f;
			RandPos.x = 1500;
			RandPos.y = 750;
			locationCount = 0;
			break;
		default:
			break;
		}
	}
}

void Enemy1::monsterPatten2()
{
	if (!angleCheck)
	{
		this->EAngle = this->GetAngle();
		angleCheck = true;
	}
	else
	{
		RandPos.y = 1000;
		speed = 2.0f;
	}
}
