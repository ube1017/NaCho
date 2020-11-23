#include "Enemy1.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy1::Init()
{
	hp = 10;
	damge = 1;
	speed = 1.0f;
	missileSpeed = 1.0f;
	size.cx = 30;
	size.cy = 60;
	hitBoxSize = size;
	locationCount = 0;
	mapInCheck = false;
	mapOutCheck = false;

	// 시작 위치 설정
	RandLocation();
	LocationReset();
	checkTime = 0;

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
	Enemy::Update();

	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;


	imageinfo.MovePos(pos);
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
				(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

	if (!AutomaticMissile)
	{
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{
				// 탄 발사전 좌표지정
				PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
				// 각도를 받고
				Missile* Em1 = playScene->SpawnMissile(this, "EnemyMissile", this->pos, { 30, 30 });

				Em1->SetAngle(this->GetAngle());		// 각도 값
				Em1->SetSpeed(missileSpeed);			// 총알 스피드
				Em1->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			   //그 각도로 움직이는 코드
				LocationReset();
				//	moveTime = 0;
				AutomaticMissile = true;
			}
		}
	}
	else if (AutomaticMissile)
	{
		checkTime += TimerManager::GetSingleton()->GettimeElapsed();
		if (checkTime >= 2.0f)
		{
			checkTime = 0;
			AutomaticMissile = false;
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
	//RandNum = rand() % 2;
	RandPos.x = WINSIZE_X / 2 + 400;
	RandPos.y = -100;
	/*if (RandNum == 0)
	{
		RandPos.y = -100;
	}
	else if (RandNum == 1)
	{
		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x = 1000;
		}
		else
		{
			RandPos.x = 0;
		}
	}*/
	this->pos.x = RandPos.x;
	this->pos.y = RandPos.y;
	imageinfo.MovePos(RandPos);
}

void Enemy1::LocationReset()
{
	locationCount++;
	monsterPatten(locationCount);
	//monsterPatten2();
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
		speed = 0.5f;
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
		break;
	default:
		break;
	}
}

void Enemy1::monsterPatten2()
{	
	RandPos.x += pattenX;
	RandPos.y - 5;

	if (RandPos.x == 950)
	{
		RandPos.x = 900;
		RandPos.y = 75;
		pattenX *= -1;
	}
}
