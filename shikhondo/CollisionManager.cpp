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

void CollisionManager::CollisinCheck()
{
	list<Enemy*>* enemy = const_cast<list<Enemy*>*>(enemyManager->GetSpawnEnemyList());
	list<Missile*>* missile = const_cast<list<Missile*>*>(missileManager->GetSpawnMissileList());
	player;


	list<Missile*>::iterator missileit = missile->begin();
	for (; missileit != missile->end(); missileit++)
	{

	}

}

