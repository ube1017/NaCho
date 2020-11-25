#include "CollisionManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Enemy.h"
#include "GamePlayStatic.h"


HRESULT CollisionManager::Init()
{
	
	return S_OK;
}

void CollisionManager::Release()
{
	GameNode::Release();
}

void CollisionManager::Update()
{
	GameNode::Update();
	this->CollisinCheck();
}

void CollisionManager::Render(HDC hdc)
{
	GameNode::Render(hdc);
	FPOINT playerPos = player->Getpos();
	SIZE playerSize = player->GetSize();
	playerSize = { playerSize.cx - 30, playerSize.cy - 30 };
	Rectangle(hdc,  (int)(playerPos.x - playerSize.cx /2), (int)(playerPos.y - playerSize.cy /2), 
					(int)(playerPos.x + playerSize.cx /2), (int)(playerPos.y + playerSize.cy /2));
}

void CollisionManager::CollisinCheck()
{
	list<Enemy*>* enemys = const_cast<list<Enemy*>*>(enemyManager->GetSpawnEnemyList());
	list<Missile*>* missile = const_cast<list<Missile*>*>(missileManager->GetSpawnMissileList());
	deque<Missile*> releaseMissiles;
	deque<Enemy*> releaseEnemy;

	Missile* emissile;
	list<Missile*>::iterator missileit = missile->begin();
	FPOINT playerPos = player->Getpos();
	SIZE playerSize = player->GetSize();
	playerSize = { playerSize.cx - 30, playerSize.cy - 30 };
	RECT playerHitBox = player->GetHitBox();
	//RECT missileHitBox;
	FPOINT otherPos;
	POINT pos;
	if (!player->GetIsInvincibility())
	{
		for (; missileit != missile->end(); missileit++)
		{
			emissile = *missileit;
			otherPos = emissile->GetPos();
			if (!emissile->GetIsValid())
				releaseMissiles.push_back(*missileit);
			if (playerPos.x - playerSize.cx <= otherPos.x &&
				playerPos.x + playerSize.cx >= otherPos.x)
			{
				if (playerPos.y - playerSize.cy <= otherPos.y &&
					playerPos.y + playerSize.cy >= otherPos.y)
				{
					pos = { (LONG)otherPos.x,(LONG)otherPos.y };
					if (!emissile->GetIsSoul())
						player->AddSoulGauge(1);
					if (PtInRect(&playerHitBox, pos))
					{
						player->OnHit(emissile);
						emissile->OnHit();
						releaseMissiles.push_back(*missileit);
						DEBUG_MASSAGE("플레이어 충돌\n");
					}

				}
			}
		}
	}
	list<Enemy*>::iterator eiter = enemys->begin();
	list<Missile*>* playerMissile = const_cast<list<Missile*>*>(missileManager->GetSpawnPlayerMissileList());
	FPOINT enemyPos;
	SIZE enemySize;
	RECT enemyRect;
	Enemy* enemy;
	if (player->GetBoomAttackCount() != 0)
	{
		Missile* boomMissile = player->GetBoomMissile();
		RECT boomBox = boomMissile->GetHitBox();
		for (; eiter != enemys->end(); )
		{
			if (!(*eiter)->GetMapInCheck())
			{
				eiter++;
				continue;
			}
			enemy = *eiter;
			eiter++;
			enemyPos = enemy->Getpos();
			pos = { (LONG)enemyPos.x , (LONG)enemyPos.y };
			if (PtInRect(&boomBox, pos))
			{
				enemy->OnHit(boomMissile);
				if (!enemy->GetisActivation())
					enemyManager->DieEnemy(enemy);
			}
		}
		boomMissile->SetHitBox({0,0,0,0});
	}

	eiter = enemys->begin();
	
	for (; eiter != enemys->end(); eiter++)
	{
		if (!(*eiter)->GetMapInCheck())
			continue;
		enemyPos = (*eiter)->Getpos();
		enemySize = (*eiter)->GetSize();
		for (missileit = playerMissile->begin(); missileit != playerMissile->end(); missileit++)
		{
			emissile = *missileit;
			otherPos = emissile->GetPos();
			if (enemyPos.x - enemySize.cx <= otherPos.x &&
				enemyPos.x + enemySize.cx >= otherPos.x)
			{
				if (enemyPos.y - enemySize.cy <= otherPos.y &&
					enemyPos.y + enemySize.cy >= otherPos.y)
				{
					pos = { (LONG)otherPos.x,(LONG)otherPos.y };
					enemyRect = (*eiter)->GetHitBox();
					if (PtInRect(&enemyRect, pos))
					{
						(*eiter)->OnHit(emissile);
						emissile->OnHit();
						releaseMissiles.push_back(*missileit);
						if (!(*eiter)->GetisActivation())
						{
							releaseEnemy.push_back(*eiter);
							break;
						}
						if (player->GetIsSpecialAbility())
							GamePlayStatic::GetScene()->SetAllShaek(1,-1,0.1f);
						
						DEBUG_MASSAGE("적충돌 충돌\n");
					}

				}
			}
		}


	}


	for (int i = 0; i < releaseMissiles.size();i++)
		missileManager->MissileRelease(releaseMissiles[i]->GetOnwer(), releaseMissiles[i]);
	for (int i = 0; i < releaseEnemy.size();i++)
		enemyManager->DieEnemy(releaseEnemy[i]);
	releaseMissiles.clear();
	releaseEnemy.clear();
}

