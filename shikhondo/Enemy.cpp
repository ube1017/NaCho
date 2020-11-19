#include "Enemy.h"
#include "GamePlayStatic.h"

HRESULT Enemy::Init()
{
	return E_NOTIMPL;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
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
