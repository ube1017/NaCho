#include "Enemy3.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy3::Init()
{
	hp = 100;
	damge = 1;
	speed = 2.0f;
	missileSpeed = 2.0f;
	size.cx = 40;
	size.cy = 70;
	hitBoxSize = size;
	locationCount = 0;
	ShootCount = 0;
	angleNum = 50;
	mapInCheck = false;
	mapOutCheck = false;
	// 시작 위치 설정
	RandLocation();
	LocationReset();
	////imageinfo.imageName = "enemy1";
	imageinfo.DrawRectSetting("enemy3", this->pos, { 145,158 }, true, { 145,158 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy3::Idle, 0.070f);
	return E_NOTIMPL;
}

void Enemy3::Release()
{
}

void Enemy3::Update()
{
	Enemy::Update();
	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
			(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };
	imageinfo.MovePos(pos);

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (checkTime >= 0.5f)
	{
		if (!AutomaticMissile)
		{
			if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
			{
				if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
				{// 탄 발사전 좌표지정
					PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
					// 각도를 받고
					for (int i = 0; i < 5; i++)
					{
						Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
						Em->SetAngle(DegreeToRadian(angleNum));		// 각도 값
						Em->SetSpeed(missileSpeed);					// 총알 스피드
						Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
						angleNum += 20;
					}
					angleNum = 50;
					ShootCount++;
					//그 각도로 움직이는 코드
					checkTime = 0;

					if (ShootCount > 3)
					{
						checkTime = 0;
						AutomaticMissile = true;
						speed = 0;
					}
				}
			}
		}
		else if (AutomaticMissile)
		{
			if (checkTime >= 1.0f)
			{
				LocationReset();
				ShootCount = 0;
				checkTime = 0;
				AutomaticMissile = false;
				speed = 2.0f;
			}
		}
	}
	
}

void Enemy3::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
#ifdef _DEBUG
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
#endif // _DEBUG

	
}

void Enemy3::RandLocation()
{
	RandNum = rand() % 2;
	RandPos.x = rand() % PlayXSize + Play_LeftX;
	RandPos.y = rand() % (WINSIZE_Y / 2);
	if (RandNum == 0)
	{
		RandPos.y *= -1;
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
	}

	this->pos.x = RandPos.x;
	this->pos.y = RandPos.y;
	imageinfo.MovePos(RandPos);
}

void Enemy3::LocationReset()
{
	locationCount++;
	switch (locationCount)
	{
	case 1:
		RandPos.x = WINSIZE_X / 2;
		RandPos.y = 200;
		break;
	case 2:
		RandPos.x = WINSIZE_X / 2 + 200;
		RandPos.y = 200 + 75;
		break;
	case 3:
		RandPos.x = WINSIZE_X / 2 + 200;
		RandPos.y = 200 + 150;
		break;
	case 4:
		RandPos.x = WINSIZE_X / 2;
		RandPos.y = 200 + 200;
		break;
	case 5:
		RandPos.x = WINSIZE_X / 2 - 200;
		RandPos.y = 200 + 150;
		break;
	case 6:
		RandPos.x = WINSIZE_X / 2 - 200;
		RandPos.y = 200 + 75;
		locationCount = 0;
		break;
	default:
		break;
	}
}

void Enemy3::Death()
{
	Character::Death();
	TimerManager::GetSingleton()->DeleteTimer(idleTimer);
}

void Enemy3::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framey < 2)
	{
		if (imageinfo.framex > 2)
		{
			imageinfo.framex = 0;
			imageinfo.framey++;
		}
	}
	else
	{
		if (imageinfo.framex > 1)
		{
			imageinfo.framex = 0;
			imageinfo.framey = 0;

		}
	}
}
