#include "Enemy.h"
#include "GamePlayStatic.h"
#include "Missile.h"
#include "Player.h"
#include "PlayScene.h"
#include "EnemyManager.h"

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
		if (pos.x < Play_LeftX || pos.x > Play_RightX)
		{
			mapOutCheck = true;
		}
		if (pos.y < 0 || pos.y > WINSIZE_Y)
		{
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
	Player* player = Cast<Player>(hitMissile->GetOnwer());
	int dmage = player->GetDamge();
	this->hp -= damge;
	if (this->hp <= 0)
		this->Death();

}
