#pragma once
#include"Scene.h"
class PlayScene : public Scene
{
public:
	//  ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init();
	// �޸� ����
	void Release();
	// ������ ���� ���� ���� ���� ( ������ ����)
	void Update();
	// ������ ���� ��� (�̹���, �ؽ�Ʈ)
	void Render(HDC hdc);
private:

	class Player* player;
	class BackGround* backGround;
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
};

