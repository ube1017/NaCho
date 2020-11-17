#pragma once
#include "pch.h"
#include "Singleton.h"
class MainGame;
class Enemy;

class EnemyManager : public Singleton<EnemyManager>
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
		Enemy* enemy = mainGame->CreateObject<T>();
		enemyList.push_back(enemy);
	}

private:
	// 객체를 만들 메인 게임.
	MainGame* mainGame;
	list<Enemy*> enemyList;
};

