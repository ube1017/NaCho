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
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

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
	// ��ü�� ���� ���� ����.
	MainGame* mainGame;
	list<Enemy*> enemyList;
};

