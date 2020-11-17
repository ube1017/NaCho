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
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetMainGame(MainGame* mainGame) { this->mainGame = mainGame; }
	const list<Enemy*>* GetenemyList() { return &enemyList; }

	template<typename T>
	Enemy* SpwanEeney()
	{
		Enemy* enemy = mainGame->CreateObject<T>();
		enemyList.push_back(enemy);
	}

private:
	// ��ü�� ���� ���� ����.
	MainGame* mainGame;
	list<Enemy*> enemyList;
};

