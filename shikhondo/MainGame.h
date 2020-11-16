#pragma once

/*
	���漱��, ��ó���� #include

	1. is a ���� : �ҳ�Ÿ�� ����.					-> #include
	2. has a ���� : �ҳ�Ÿ�� ������ ������ �ִ�.	-> ���漱��
*/
#include "GameNode.h"

class Tank;
class Enemy;
class Missile;
class Image;
class EnemyManager;
class SpaceShip;
class MainGame : public GameNode
{
private:
	struct MOUSE_DATA
	{
		int mousePosX, mousePosY;
		int clickedPosX, clickedPosY;
	};

	HDC hdc;
	//PAINTSTRUCT ps;
	//HANDLE hTimer;
	MOUSE_DATA mouseData;
	bool isInit;

	SpaceShip* spaceShip;
	Tank* tank1;
	Enemy* enemy1;
	EnemyManager* enemyMgr;

	Image* backBuffer;
	Image* backGround;
	int random;

public:
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	bool CheckCollision(Missile* m1, Missile* m2);	// �̻��ϳ��� �浹Ȯ��
	float GetDistance(FPOINT pos1, FPOINT pos2);
	float GetAngle(FPOINT pos1, FPOINT pos2);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

