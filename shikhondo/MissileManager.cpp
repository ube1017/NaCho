#include "MissileManager.h"
#include "Missile.h"
#include "MainGame.h"
#include "GamePlayStatic.h"
#include "Character.h"

HRESULT MissileManager::Init()
{
	SetIsValid(false);
	return E_NOTIMPL;
}

void MissileManager::Release()
{
}

void MissileManager::Update()
{
}

void MissileManager::Render(HDC hdc)
{
}

Missile * MissileManager::CreateMissile(FPOINT pos)
{
	Missile* spwanMissile = GamePlayStatic::GetMainGame()->CreateObject<Missile>();
	spwanMissile->SetPos(pos);
	spwanMissile->SetIsValid(false);
	return spwanMissile;
}

Missile* MissileManager::SpwanMissile(Character* onwer, FPOINT pos)
{
	list<Missile*>::iterator mit;
	Missile* missile;
	for (mit = missileList.begin(); mit != missileList.end(); mit++)
	{
		missile = *mit;
		if (!missile->GetIsValid())
		{
			missile->SetIsValid(true);
			missile->SetOwner(onwer);
			missile->SetPos(pos);
			missileList.splice(missileList.end(), missileList, mit);

			return missile;
		}
	}
	return nullptr;
}
