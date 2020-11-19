#include "Enemy2.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy2::Init()
{
	hp = 30;
	damge = 1;
	speed = 1.0f;
	size.cx = 150;
	size.cy = 150;
	locationCount = 0;
	countSize = 0;
	ShootCount = 0;
	ImageSize1 = -1.0f;
	ImageSize2 = 1.0f;
	mapInCheck = false;
	mapOutCheck = false;
	// 시작 위치 설정
	RandLocation();
	LocationReset();

	////imageinfo.imageName = "enemy1";
	CircleImage.DrawRectSetting("enemy2_1", this->pos, size, true, { 400,400 });
	imageinfo.DrawRectSetting("enemy2_2", this->pos, size, true, { 500,500 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy2::Idle, 0.07f);
	return E_NOTIMPL;
}

void Enemy2::Release()
{
}

void Enemy2::Update()
{
	Enemy::Update();
	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

	CircleImage.MovePos(pos);
	imageinfo.MovePos(pos);

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (checkTime >= 0.1f)
	{
		if (!AutomaticMissile)
		{
			if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
			{
				if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
				{// 탄 발사전 좌표지정
					PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
					// 각도를 받고
					Missile* Em1 = playScene->SpawnMissile(this, "21", { pos.x - (CircleImage.size.cx / 2), pos.y }, { 20, 20 });
					Missile* Em2 = playScene->SpawnMissile(this, "21", { pos.x + (CircleImage.size.cx / 2), pos.y }, { 20, 20 });
					Em1->SetAngle(this->GetAngle({ pos.x - (CircleImage.size.cx / 2), pos.y }));		// 각도 값
					Em1->SetSpeed(speed);					// 총알 스피드
					Em1->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
					Em2->SetAngle(this->GetAngle({ pos.x + (CircleImage.size.cx / 2), pos.y }));		// 각도 값
					Em2->SetSpeed(speed);					// 총알 스피드
					Em2->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴

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
			if (checkTime >= 2.0f)
			{
				LocationReset();
				ShootCount = 0;
				checkTime = 0;
				AutomaticMissile = false;
				speed = 1.0f;
			}
		}
	}
	// 이미지 조정
	countSize++;
	if (countSize == 5)
	{
		CircleImage.size.cx += (LONG)ImageSize1;
		CircleImage.size.cy += (LONG)ImageSize1;
		imageinfo.size.cx += (LONG)ImageSize2;
		imageinfo.size.cy += (LONG)ImageSize2;
		if (CircleImage.size.cx == 150 || CircleImage.size.cx == 100)
		{
			ImageSize1 *= -1;
		}
		if (imageinfo.size.cx == 175 || imageinfo.size.cx == 150)
		{
			ImageSize2 *= -1;
		}
		countSize = 0;
	}

}

void Enemy2::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, CircleImage);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	//Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
}

void Enemy2::RandLocation()
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
	CircleImage.MovePos(RandPos);
}

void Enemy2::LocationReset()
{
	locationCount++;
	if (locationCount < 3)
	{
		RandPos.x = (rand() % (PlayXSize - size.cx)) + (size.cx / 2 + Play_LeftX);
		RandPos.y = (rand() % (WINSIZE_Y / 2 - size.cy)) + (size.cy / 2);
	}
	else
	{
		RandPos.x = rand() % PlayXSize + Play_LeftX;
		RandPos.y = rand() % (WINSIZE_Y / 2) + 50;

		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x = 1200;
		}
		else
		{
			RandPos.x = -100;
		}
		locationCount = 0;
	}
}

void Enemy2::Death()
{
	Character::Death();
	TimerManager::GetSingleton()->DeleteTimer(idleTimer);
}

void Enemy2::Idle()
{
	imageinfo.framex++;
	CircleImage.framex++;
	if (CircleImage.framex > 8)
	{
		CircleImage.framex = 0;
	}
	if (imageinfo.framex > 11)
	{
		imageinfo.framex = 0;
	}
}
