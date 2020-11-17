#include "EnemyManager.h"

HRESULT EnemyManager::Init()
{
	SetIsValid(false);
	return S_OK;
}

void EnemyManager::Release()
{
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
	for (eit = enemyList.begin(); eit != enemyList.end(); eit++)
	{
		if (enemy == *eit)
		{
			Enemy* enemy = *eit;
			enemy->SetIsValid(false);
			enemyList.splice(enemyList.begin(), enemyList, eit);
			break;
		}
	}
}
