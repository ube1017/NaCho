#include "Enemy.h"
#include "GamePlayStatic.h"
#include "Missile.h"
#include "Player.h"
#include "PlayScene.h"
#include "EnemyManager.h"
#include "Impact.h"

Enemy::Enemy()
{
	impact = GamePlayStatic::GetScene()->CreateObject<Impact>();
	impact->SetIsValid(false);
	impact->SetZOrder(8);
}

HRESULT Enemy::Init()
{
	return E_NOTIMPL;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	if (!mapInCheck && !mapOutCheck)
	{
		if (pos.y > 0 && pos.y < WINSIZE_Y)
		{
			if (pos.x > Play_LeftX && pos.x < Play_RightX)
			{
				mapInCheck = true;
			}
		}
	}
	else if (mapInCheck && !mapOutCheck)
	{
		if (pos.x < Play_LeftX - size.cx / 2|| pos.x > Play_RightX + size.cx / 2)
		{
			PlayScene* plsyScene = Cast<PlayScene>(GamePlayStatic::GetScene());
			plsyScene->GetEnemyManager()->DieEnemy(this);
			isActivation = false;
			mapOutCheck = true;
		}
		if (pos.y < -size.cy / 2|| pos.y > WINSIZE_Y + size.cy / 2)
		{
			PlayScene* plsyScene = Cast<PlayScene>(GamePlayStatic::GetScene());
			plsyScene->GetEnemyManager()->DieEnemy(this);
			isActivation = false;
			mapOutCheck = true;
		}
	}
}

void Enemy::Render(HDC hdc)
{
}

float Enemy::GetAngle()
{
	FPOINT pos = GamePlayStatic::GetPlayerCharacter()->Getpos();
	return atan2f((pos.y - this->pos.y), (pos.x - this->pos.x));
}


float Enemy::GetAngle(FPOINT GetPos)
{
	FPOINT pos = GamePlayStatic::GetPlayerCharacter()->Getpos();
	return atan2f((pos.y - GetPos.y), (pos.x - GetPos.x));
}

void Enemy::OnHit(Missile* hitMissile) 
{
	Character::OnHit(hitMissile);
	//Character* owner = hitMissile->GetOnwer()
	//Player* player = Cast<Player>(hitMissile->GetOnwer());
	//int dmage = player->GetDamge();
	int hitdmage = hitMissile->GetDamage();
	
	this->hp -= hitdmage;
	if (this->hp <= 0)
	{
		impact->SetIsValid(true);
		impact->SpawnImpact("Impact", this->pos, {256,256}, 0.01f);
		this->Death();
	}
}
