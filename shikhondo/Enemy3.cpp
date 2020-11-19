#include "Enemy3.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy3::Init()
{
	hp = 50;
	damge = 1;
	speed = 1.0f;
	size.cx = 40;
	size.cy = 70;
	locationCount = 0;
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
	if (RandPos.x != pos.x)
	{
		if (RandPos.x > pos.x)
		{
			pos.x += speed;
		}
		else if (RandPos.x < pos.x)
		{
			pos.x -= speed;
		}
	}
	if (RandPos.y != pos.x)
	{
		if (RandPos.y > pos.y)
		{
			pos.y += speed;
		}
		else if (RandPos.y < pos.y)
		{
			pos.y -= speed;
		}
	}
	imageinfo.MovePos(pos);
}

void Enemy3::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
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
