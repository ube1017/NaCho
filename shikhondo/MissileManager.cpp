#include "MissileManager.h"
#include "Missile.h"
#include "MainGame.h"
#include "GamePlayStatic.h"
#include "Character.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

HRESULT MissileManager::Init()
{
	SetIsValid(false);
	isNotUPdate = true;
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
	Missile* spwanMissile = GamePlayStatic::GetScene()->CreateObject<Missile>();
	spwanMissile->SetPos(pos);
	spwanMissile->SetIsValid(false);
	missileList.push_back(spwanMissile);
	return spwanMissile;
}

Missile* MissileManager::SpawnMissile(Character* onwer, string imageName, FPOINT pos, SIZE size)
{
	list<Missile*>::iterator mit;
	Missile* missile;
	for (mit = missileList.begin(); mit != missileList.end(); mit++)
	{
		missile = *mit;
		if (!missile->GetIsValid())
		{
			missile->SetIsValid(true);
			missile->Init();
			missile->SetOwner(onwer);
			missile->SetPos(pos);
			missile->MissileSetting(imageName,pos,size);
			missile->SetZOrder(8);
			spawnMissileList.push_back(missile);
			missileList.splice(missileList.end(), missileList, mit);
			return missile;
		}
	}
	return nullptr;
}

Missile * MissileManager::SpawnPlayerMissile(Character* onwer, string imageName, FPOINT pos, SIZE size)
{
	list<Missile*>::iterator mit;
	Missile* missile;
	for (mit = missileList.begin(); mit != missileList.end(); mit++)
	{
		missile = *mit;
		if (!missile->GetIsValid())
		{
			// 활성화 = true 비활성화 = false
			missile->SetIsValid(true);
			// 미사일의 주인설정
			missile->Init();
			missile->SetOwner(onwer);
			// 미사일의 시작위치
			missile->SetPos(pos);
			// 미사일의 이미지 값 설정
			missile->MissileSetting(imageName, pos, size);
			spawnPlayerMissileList.push_back(missile);
			missile->SetZOrder(9);
			// 리스트에서 위치변경
			missileList.splice(missileList.end(), missileList, mit);
			return missile;
		}
	}
	return nullptr;
}

void MissileManager::MissileRelease(Character* onwer, Missile* missile)
{
	if (missile == nullptr)
		return;
	if (Cast<Player>(onwer))
	{
		list<Missile*>::iterator mit;
		for (mit = spawnPlayerMissileList.begin(); mit != spawnPlayerMissileList.end(); mit++)
		{
			if (*mit == missile)
			{
				//missile->SetIsValid(false);
				missile->SetOwner(nullptr);
				missile->SetPos({ -10,-10 });
				missile->SetSize({ 0,0 });
				missile->MissileSetting("", { -10,-10 }, { 0,0 });
				spawnPlayerMissileList.erase(mit);
				return;
			}
		}
	}
	else
	{
		list<Missile*>::iterator mit;
		for (mit = spawnMissileList.begin(); mit != spawnMissileList.end(); mit++)
		{
			if (*mit == missile)
			{
				//missile->SetIsValid(false);
				missile->SetOwner(nullptr);
				missile->SetPos({ -10,-10 });
				missile->SetSize({ 0,0 });
				missile->MissileSetting("", { -10,-10 }, { 0,0 });
				spawnMissileList.erase(mit);
				return;
			}
		}
	}


}

void MissileManager::MissileAllChangeSoul(Character* taget)
{
	list<Missile*>::const_iterator const_it;
	for (const_it = spawnMissileList.begin(); const_it != spawnMissileList.end(); const_it++)
	{
		//(*const_it)->OnHit();
		(*const_it)->ChangeSoul(taget);
	}
}
