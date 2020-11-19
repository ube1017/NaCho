#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT EnemyBoss::Init()
{
	hp = 1000;
	damge = 1;
	speed = 1.0f;
	size.cx = 250;
	size.cy = 200;

	// 시작 위치 설정
	RandLocation();
	////imageinfo.imageName = "enemy1";
	   //imageinfo.DrawRectSetting("enemy1", this->pos, { 145,155 }, true, { 145,155 });
	   //TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy1::Idle, 0.035f);
	return E_NOTIMPL;
}

void EnemyBoss::Release()
{
	
}

void EnemyBoss::Update()
{
	//imageinfo.MovePos(pos);
}

void EnemyBoss::Render(HDC hdc)
{
	//ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, pos.x, pos.y, pos.x + (size.cx), pos.y + (size.cy));
}

void EnemyBoss::RandLocation()
{
	this->pos.x = Play_LeftX +200;
	this->pos.y = 20;
	//imageinfo.MovePos(this->pos);
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
