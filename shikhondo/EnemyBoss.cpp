#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT EnemyBoss::Init()
{
	hp = 1000;
	damge = 1;
	speed = 1.0f;
	size.cx = 80;
	size.cy = 160;

	// 시작 위치 설정
	RandLocation();
	////imageinfo.imageName = "enemy1";
	imageinfo.DrawRectSetting("Boss", this->pos, { 110,220 }, true, { 204,403 });
	//TimerManager::GetSingleton()->SetTimer(idleTimer, this, &EnemyBoss::Idle, 0.035f);
	return E_NOTIMPL;
}

void EnemyBoss::Release()
{
	
}

void EnemyBoss::Update()
{
	imageinfo.MovePos(pos);
}

void EnemyBoss::Render(HDC hdc)
{
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy /2));
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
}

void EnemyBoss::RandLocation()
{
	this->pos.x = WINSIZE_X / 2;
	this->pos.y = 150;
	imageinfo.MovePos(this->pos);
}

void EnemyBoss::LocationReset()
{

}

void EnemyBoss::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 3)
		imageinfo.framex = 0;
}
