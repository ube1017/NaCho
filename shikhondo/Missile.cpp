#include "Missile.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "GamePlayStatic.h"
#include "Character.h"

Missile::Missile()
{
	nowMovePatten = Patten::NORMALMOVE;
	movePatten[MISSILEPATTEN(Patten::NORMALMOVE)] = &Missile::NormalMove;
	movePatten[MISSILEPATTEN(Patten::HOMINGMOVE)] = &Missile::HomingMove;
}

HRESULT Missile::Init()
{
	this->imaginfo.imageName = "";
	this->imaginfo.drwrc = { 0,0,0,0 };
	this->imaginfo.size = {0,0};
	this->imaginfo.framex = 0;
	this->imaginfo.framey = 0;
	isNotUPdate = false;
	return S_OK;
}

void Missile::Release()
{
	GameNode::Release();
}

void Missile::Update()
{
	GameNode::Update();
	(this->*movePatten[MISSILEPATTEN(nowMovePatten)])();
	if (pos.x <= Play_LeftX || pos.x >= Play_RightX ||
		pos.y <= 0 || pos.y >= WINSIZE_Y)
	{
		this->MissileRelease();
		this->isActivation = false;
	}

}

void Missile::Render(HDC hdc)
{
	GameNode::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imaginfo);
}

void Missile::MissileSetting(string imageName, FPOINT pos, SIZE size)
{
	this->pos = pos;
	this->size = size;
	this->imaginfo.DrawRectSetting(imageName,pos,size);
}

void Missile::MissileRelease()
{
	PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
	playScene->GetMissileManager()->MissileRelease(owner,this);
}

void Missile::SetMovePatten(Patten movePatten)
{
	nowMovePatten = movePatten;
}

void Missile::OnHit()
{
	this->MissileRelease();
	this->isActivation = false;
}

void Missile::NormalMove()
{
	this->pos.y += speed;
	this->imaginfo.MovePos(this->pos);

}

void Missile::HomingMove()
{
	FPOINT tagetPos = taget->Getpos();
	angle = atan2f((tagetPos.y - pos.y), (tagetPos.x - pos.x));
	pos.x += speed * cosf(angle);
	pos.y += speed * sinf(angle);
	imaginfo.MovePos(pos);
}
