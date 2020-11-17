#pragma once
#include "pch.h"
#include "GameNode.h"
#include "Scene.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
public:
	HRESULT Init();
	void Release();
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetMainGame(Scene* scene) { this->scene = scene; }
	const list<Enemy*>* GetenemyList() { return &enemyList; }

	template<typename T>
	Enemy* CreateEeney(MissileManager* missileManager = nullptr)
	{
		Enemy* enemy = Cast<Enemy>(scene->CreateObject<T>());
		enemy->SetIsValid(false);
		enemy->missileManager(missileManager);
		enemyList.push_back(enemy);
		return enemy;
	}

	template<typename T>
	Enemy* CreateEeney(FPOINT pos, MissileManager* missileManager = nullptr)
	{
		Enemy* enemy = Cast<Enemy>(scene->CreateObject<T>());
		enemy->SetPos(pos);
		enemy->missileManager(missileManager);
		enemyList.push_back(enemy);
		return enemy;
	}

	template<typename T>
	Enemy* SpwanEeney()
	{
		list<Enemy*>::iterator eit;
		for (eit = enemyList.begin(); eit != enemyList.end() ;eit++)
		{
			T* SeletEnemy = Cast<T>(*eit);
			if (SeletEnemy != nullptr)
			{
				Enemy* enemy = *eit;
				if (!enemy->GetIsValid())
				{
					enemy->SetIsValid(true);
					enemy->Init();
					enemyList.splice(enemyList.end(),enemyList,eit);
					return enemy;
				}
			}
		}
		return nullptr;
	}

	void DieEnemy(Enemy* enemy);


private:
	// ��ü�� ���� ���� ����.
	Scene* scene;
	list<Enemy*> enemyList;
};

