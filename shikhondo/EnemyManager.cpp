#include "EnemyManager.h"

HRESULT EnemyManager::Init()
{
	SetIsValid(false);
	return S_OK;
}

void EnemyManager::Release()
{
	GameNode::Release();
	list<Enemy*>::iterator eit;
	for (eit = enemyList.begin(); eit != enemyList.end(); eit++)
	{
		Enemy* enemy = *eit;
		enemy->Release();
		delete enemy;
	}
	enemyList.clear();
	spawnEnemyList.clear();
}

void EnemyManager::Update()
{
}

void EnemyManager::Render(HDC hdc)
{
}

void EnemyManager::DieEnemy(Enemy* enemy)
{
	list<Enemy*>::iterator eit;
	for (eit = spawnEnemyList.begin(); eit != spawnEnemyList.end(); eit++)
	{
		if (enemy == *eit)
		{
			Enemy* enemy = *eit;
			enemy->Death();
			spawnEnemyList.erase(eit);
			break;
		}
	}
}
