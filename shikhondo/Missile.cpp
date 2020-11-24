#include "Missile.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "GamePlayStatic.h"
#include "Character.h"
#include "Image.h"

Missile::Missile()
{
	zOrder = 9;
	nowMovePatten = Patten::NORMALMOVE;
	movePatten[MISSILEPATTEN(Patten::NORMALMOVE)] = &Missile::NormalMove;
	movePatten[MISSILEPATTEN(Patten::HOMINGMOVE)] = &Missile::HomingMove;
	movePatten[MISSILEPATTEN(Patten::ANGLEMOVE)] = &Missile::AngleMove;



	misiileAnimTimerHandle.timerName = "미사일 애니메이션";
}

HRESULT Missile::Init()
{
	this->imaginfo.imageName = "";
	this->imaginfo.drwrc = { 0,0,0,0 };
	this->imaginfo.size = {0,0};
	this->imaginfo.framex = 0;
	this->imaginfo.framey = 0;
	this->isNotUPdate = false;
	this->isSoul = false;
	this->taget = nullptr;
	this->damage = 1;
	this->hitBox = { 0,0,0,0};
	
	return S_OK;
}

void Missile::Release()
{
	GameNode::Release();
}

void Missile::Update()
{
	GameNode::Update();
	this->imaginfo.MovePos(this->pos);
	(this->*movePatten[MISSILEPATTEN(nowMovePatten)])();
	if (pos.x <= Play_LeftX || pos.x >= Play_RightX ||
		pos.y <= 0 || pos.y >= WINSIZE_Y)
	{
		this->MissileRelease();
		this->isActivation = false;
		TimerManager::GetSingleton()->DeleteTimer(misiileAnimTimerHandle);
	}

}

void Missile::Render(HDC hdc)
{
	GameNode::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imaginfo);
}

void Missile::OnHit()
{
	// this->MissileRelease();
	this->isActivation = false;
	TimerManager::GetSingleton()->DeleteTimer(misiileAnimTimerHandle);
}

void Missile::MissileSetting(string imageName, FPOINT pos, SIZE size)
{
	this->pos = pos;
	this->size = size;
	this->imaginfo.DrawRectSetting(imageName,pos,size);
	TimerManager::GetSingleton()->SetTimer(misiileAnimTimerHandle, this, &Missile::MissileAnim, 0.05f);
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

void Missile::ChangeSoul(Character * taget)
{
	this->isSoul = true;
	this->taget = taget;
	this->nowMovePatten = Patten::HOMINGMOVE;
	this->speed = 8;
	this->imaginfo.DrawRectSetting("Soulgeiji2", this->pos, {80,80});
}

void Missile::NormalMove()
{
	this->pos.y += speed;
	this->imaginfo.MovePos(this->pos);

}

void Missile::HomingMove()
{
	if (taget->GetisActivation())
	{
		FPOINT tagetPos = taget->Getpos();
		angle = atan2f((tagetPos.y - pos.y), (tagetPos.x - pos.x));
		pos.x += speed * cosf(angle);
		pos.y += speed * sinf(angle);
		imaginfo.MovePos(pos);
	}
	else
	{
		pos.x += speed * cosf(angle);
		pos.y += speed * sinf(angle);
		imaginfo.MovePos(pos);
	}
}

void Missile::AngleMove()
{
	pos.x += cosf(this->angle) * speed;
	pos.y += sinf(this->angle) * speed;
	imaginfo.MovePos(pos);
}

void Missile::SevenMove()
{

}

void Missile::MissileAnim()
{
	if (isActivation)
	{
		Image* findImage = ImageManager::GetSingleton()->FindImage(this->imaginfo.imageName);
		int X_max = findImage->GetMaxFramX();
		int Y_max = findImage->GetMaxFramY();
		this->imaginfo.framex++;
		if (this->imaginfo.framex >= X_max)
		{
			this->imaginfo.framex = 0;
			this->imaginfo.framey++;
			if (this->imaginfo.framey >= Y_max)
				this->imaginfo.framey = 0;
		}

	}
}
