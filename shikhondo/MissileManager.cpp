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
			missile->SetOwner(onwer);
			missile->SetPos(pos);
			missile->MissileSetting(imageName,pos,size);
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
			// Ȱ��ȭ = true ��Ȱ��ȭ = false
			missile->SetIsValid(true);
			// �̻����� ���μ���
			missile->SetOwner(onwer);
			// �̻����� ������ġ
			missile->SetPos(pos);
			// �̻����� �̹��� �� ����
			missile->MissileSetting(imageName, pos, size);
			spawnPlayerMissileList.push_back(missile);
			// ����Ʈ���� ��ġ����
			missileList.splice(missileList.end(), missileList, mit);
			return missile;
		}
	}
	return nullptr;
}

void MissileManager::MissileRelease(Character* onwer, Missile* missile)
{
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
				return;
			}
		}
	}


}
