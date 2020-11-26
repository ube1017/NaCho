#include "Missile.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "GamePlayStatic.h"
#include "Character.h"
#include "Image.h"
#include "Impact.h"
#include "Player.h"

Missile::Missile()
{
	zOrder = 9;
	nowMovePatten = Patten::NORMALMOVE;
	movePatten[MISSILEPATTEN(Patten::NONE)] = &Missile::NoneMove;
	movePatten[MISSILEPATTEN(Patten::NORMALMOVE)] = &Missile::NormalMove;
	movePatten[MISSILEPATTEN(Patten::HOMINGMOVE)] = &Missile::HomingMove;
	movePatten[MISSILEPATTEN(Patten::ANGLEMOVE)] = &Missile::AngleMove;
	movePatten[MISSILEPATTEN(Patten::TEST)] = &Missile::TestMove;
	movePatten[MISSILEPATTEN(Patten::TEST2)] = &Missile::TestMove2;
	
	//NONE


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
	this->isboom = false;

	angle2 = 0.0f;
	if (impact == nullptr)
	{
		impact = GamePlayStatic::GetScene()->CreateObject<Impact>();
		impact->SetZOrder(8);
	}
	impact->SetIsValid(false);
	return S_OK;
}

void Missile::Release()
{
	GameNode::Release();
}

void Missile::Update()
{
	GameNode::Update();
	//this->imaginfo.MovePos(this->pos);
	(this->*movePatten[MISSILEPATTEN(nowMovePatten)])();
	if ((pos.x <= Play_LeftX || pos.x >= Play_RightX ||
		pos.y <= 0 || pos.y >= WINSIZE_Y) && !isboom)
	{
		this->MissileRelease();
		this->isActivation = false;
		TimerManager::GetSingleton()->DeleteTimer(misiileAnimTimerHandle);
	}

}

void Missile::Render(HDC hdc)
{
	GameNode::Render(hdc);
#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
#endif // _DEBUG
	if (imaginfo.imageName != "")
		ImageManager::GetSingleton()->DrawAnimImage(hdc, imaginfo);
	
}

void Missile::OnHit()
{
	// this->MissileRelease();
	if (isboom)
		return;
	this->isActivation = false;
	Player* player = Cast<Player>(GamePlayStatic::GetPlayerCharacter());

	if (!this->isSoul)
		impact->SpawnImpact("Impact", this->pos, {128,128});
	else
		player->AddSoulScore(1);
	if (player->GetIsSpecialAbility())
		player->AddSoulScore(1);
	TimerManager::GetSingleton()->DeleteTimer(misiileAnimTimerHandle);
}

void Missile::MissileSetting(string imageName, FPOINT pos, SIZE size)
{
	this->pos = pos;
	this->size = size;
	this->imaginfo.DrawRectSetting(imageName,pos,size);
	if (!this->isboom)
		TimerManager::GetSingleton()->SetTimer(misiileAnimTimerHandle, this, &Missile::MissileAnim, 0.05f);
	else
		TimerManager::GetSingleton()->SetTimer(misiileAnimTimerHandle, this, &Missile::MissileAnim, 0.001f);
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

void Missile::NoneMove()
{
	imaginfo.MovePos(pos);
}

void Missile::TestMove()
{
	angle2 -= 0.010f;
	pos.x += speed * cosf(angle2 - angle);
	pos.y += speed * sinf(angle2 - angle);

	//this->pos.y += speed;
	this->imaginfo.MovePos(this->pos);
}

void Missile::TestMove2()
{
	angle2 += 0.010f;
	pos.x += speed * cosf(angle2 - angle);
	pos.y += speed * sinf(angle2 - angle);

	//this->pos.y += speed;
	this->imaginfo.MovePos(this->pos);
}

void Missile::MissileAnim()
{
	if (isActivation)
	{
		Image* findImage = ImageManager::GetSingleton()->FindImage(this->imaginfo.imageName);
		if (findImage)
		{
			if (this->isboom)
			{
				this->imaginfo.MovePos(MovePosType::Y_AIS, - 20);
				this->pos.y -= 20;
			}
			else
			{
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
		
	}
}
