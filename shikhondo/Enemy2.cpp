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
	// 시작 위치 설정
	RandLocation();
	LocationReset();

	////imageinfo.imageName = "enemy1";
	CircleImage.DrawRectSetting("enemy2_1", this->pos, size, true, { 400,400 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy2::Idle, 0.035f);
	imageinfo.DrawRectSetting("enemy2_2", this->pos, size, true, { 500,500 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy2::Idle, 0.035f);
	return E_NOTIMPL;
}

void Enemy2::Release()
{
}

void Enemy2::Update()
{
	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	
	CircleImage.MovePos(pos);
	imageinfo.MovePos(pos);

	if (!AutomaticMissile)
	{
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{// 탄 발사전 좌표지정
				PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
				// 각도를 받고
				Missile* Em1 = playScene->SpawnMissile(this, "21", this->pos, { 10, 10 });

				Em1->SetAngle(this->GetAngle());		// 각도 값
				Em1->SetSpeed(speed);					// 총알 스피드
				Em1->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			   //그 각도로 움직이는 코드
				checkTime = 0;
				AutomaticMissile = true;
				speed = 0;
			}
		}
	}
	else if (AutomaticMissile)
	{
		checkTime += TimerManager::GetSingleton()->GettimeElapsed();
		if (checkTime >= 2.0f)
		{
			LocationReset();

			checkTime = 0;
			AutomaticMissile = false;
			speed = 1.0f;
		}
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
