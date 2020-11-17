#include "Enemy2.h"

HRESULT Enemy2::Init()
{
	hp = 50;
	damge = 1;
	speed = 10.0f;
	size.cx = 50;
	size.cy = 50;

	// 시작 위치 설정
	RandLocation();
	LocationReset();

	return E_NOTIMPL;
}

void Enemy2::Release()
{
}

void Enemy2::Update()
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
}

void Enemy2::Render(HDC hdc)
{
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
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
}

void Enemy2::LocationReset()
{
	RandPos.x = (rand() % (PlayXSize - size.cx)) + (size.cx / 2 + Play_LeftX);
	RandPos.y = (rand() % (WINSIZE_Y / 2 - size.cy)) + (size.cy / 2);
}
