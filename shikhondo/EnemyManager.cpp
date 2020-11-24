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
			enemy->Death();
			enemy->SetPos({-10.0f,-10.f});
			spawnEnemyList.erase(eit);
			break;
		}
	}
}
