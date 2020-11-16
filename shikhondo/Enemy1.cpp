#include "Enemy1.h"

HRESULT Enemy1::Init()
{
	hp = 10;
	damge = 1;
	speed = 10.0f;
	size.cx = 10;
	size.cy = 20;

	// 시작 위치 설정
	RandLocation();


	return E_NOTIMPL;
}

void Enemy1::Release()
{
}

void Enemy1::Update()
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

void Enemy1::Render(HDC hdc)
{
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
}

void Enemy1::RandLocation()
{
	RandNum = rand() % 2;
	RandPos.x = rand() % WINSIZE_X;
	RandPos.y = rand() % (WINSIZE_Y / 2);
	if (RandNum == 0)
	{
		RandPos.y *= -1;
	}
	else if (RandNum == 1)
	{
		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x *= 2;
		}
		else
		{
			RandPos.x *= -1;
		}
	}

	this->pos.x = RandPos.x;
	this->pos.y = RandPos.y;
}

void Enemy1::LocationReset()
{
	RandPos.x = (rand() % (WINSIZE_X - size.cx)) + (size.cx / 2);
	RandPos.y = (rand() % (WINSIZE_Y / 2 - size.cy)) + (size.cy /2);
}
