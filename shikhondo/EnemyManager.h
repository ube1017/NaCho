#pragma once
#include "pch.h"
#include "GameNode.h"
#include "MainGame.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
public:
	HRESULT Init();
	void Release();
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetMainGame(MainGame* mainGame) { this->mainGame = mainGame; }
	const list<Enemy*>* GetenemyList() { return &enemyList; }

	template<typename T>
	Enemy* SpwanEeney()
	{
		Enemy* enemy = Cast<Enemy>(mainGame->CreateObject<T>());
		enemyList.push_back(enemy);
		return enemy;
	}

	template<typename T>
	Enemy* SpwanEeney(FPOINT pos)
	{
		Enemy* enemy = Cast<Enemy>(mainGame->CreateObject<T>());
		enemy->SetPos(pos);
		enemyList.push_back(enemy);
		return enemy;
	}

private:
	// 객체를 만들 메인 게임.
	MainGame* mainGame;
	list<Enemy*> enemyList;
};

