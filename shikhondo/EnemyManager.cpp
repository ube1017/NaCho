#include "EnemyManager.h"

HRESULT EnemyManager::Init()
{
	SetIsValid(false);
	isNotUPdate = true;
	return S_OK;
}

void EnemyManager::Release()
{
	GameNode::Release();
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
			//enemy->Death();
			spawnEnemyList.erase(eit);
			break;
		}
	}
}
