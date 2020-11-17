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
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

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
	// 객체를 만들 메인 게임.
	Scene* scene;
	list<Enemy*> enemyList;
};

