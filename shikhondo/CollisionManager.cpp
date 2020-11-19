#include "CollisionManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Enemy.h"


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
	Rectangle(hdc,  playerPos.x - playerSize.cx /2, playerPos.y - playerSize.cy/2, 
					playerPos.x + playerSize.cx/2, playerPos.y + playerSize.cy/2);
}

void CollisionManager::CollisinCheck()
{
	list<Enemy*>* enemy = const_cast<list<Enemy*>*>(enemyManager->GetSpawnEnemyList());
	list<Missile*>* missile = const_cast<list<Missile*>*>(missileManager->GetSpawnMissileList());

	Missile* emissile;
	list<Missile*>::iterator missileit = missile->begin();
	FPOINT playerPos = player->Getpos();
	SIZE playerSize = player->GetSize();
	RECT playerHitBox = player->GetHitBox();
	RECT missileHitBox;
	FPOINT otherPos;
	POINT pos;
	for (; missileit != missile->end(); missileit++)
	{
		emissile = *missileit;
		otherPos = emissile->GetPos();
		if (playerPos.x - playerSize.cx  <= otherPos.x && 
			playerPos.x + playerSize.cx  >= otherPos.x)
		{
			if (playerPos.y - playerSize.cy <= otherPos.y &&
				playerPos.y + playerSize.cy >= otherPos.y)
			{
				pos = { (LONG)otherPos.x,(LONG)otherPos.y };
				if (PtInRect(&playerHitBox, pos))
				{
					player->OnHit(emissile);
					emissile->OnHit();
					DEBUG_MASSAGE("�÷��̾� �浹\n");
				}

			}
		}
	}

	list<Enemy*>::iterator eiter = enemy->begin();
	list<Missile*>* playerMissile = const_cast<list<Missile*>*>(missileManager->GetSpawnPlayerMissileList());
	FPOINT enemyPos;
	SIZE enemySize;
	RECT enemyRect;
	missileit = playerMissile->begin();
	for (; eiter != enemy->end(); eiter++)
	{
		enemyPos = (*eiter)->Getpos();
		enemySize = (*eiter)->GetSize();
		for (; missileit != playerMissile->end(); missileit++)
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
						DEBUG_MASSAGE("���浹 �浹\n");
					}

				}
			}
		}

	}
}

