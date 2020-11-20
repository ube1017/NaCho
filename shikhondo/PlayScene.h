#pragma once
#include"Scene.h"

enum class SpawnPatten
{
	NONE,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	BOSS1,
};

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

	class MissileManager* GetMissileManager() { return missileManager; }
	class EnemyManager* GetEnemyManager() { return enemyManager; }

	class Missile* SpawnMissile(class Character* owner,string imageName, FPOINT missilePos, SIZE MissileSize);



	void StageSpawn();
	void SpawnPatten1();
	void SpawnPatten2();
	void SpawnPatten3();
	void SpawnBoss();
	void None() {}
private:

	class Player* player;
	class BackGround* backGround;
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
	class CollisionManager* collsionManager;
	class UI* ui;

	TimerHandle spawnTimer;
	UINT spawnCount;
	SpawnPatten nowPatten;
	UINT nextspawnCount;
	float spawnNum;
	bool isBoss;
};

