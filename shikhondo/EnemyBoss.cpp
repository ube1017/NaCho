#include "EnemyBoss.h"

HRESULT EnemyBoss::Init()
{
	hp = 10000;
	damge = 1;
	speed = 10.0f;
	size.cx = 250;
	size.cy = 200;

	// 시작 위치 설정
	RandLocation();
 
	return E_NOTIMPL;
}

void EnemyBoss::Release()
{
	
}

void EnemyBoss::Update()
{
	
}

void EnemyBoss::Render(HDC hdc)
{
	Rectangle(hdc, pos.x, pos.y, pos.x + (size.cx), pos.y + (size.cy));
}

void EnemyBoss::RandLocation()
{
	this->pos.x = Play_LeftX +200;
	this->pos.y = 20;
}

void EnemyBoss::LocationReset()
{
}
