#pragma once
#include"Scene.h"

enum class SpawnPatten
{
	ENEMY1,
	ENEMY2,
	ENEMY3,
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
private:

	class Player* player;
	class BackGround* backGround;
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
	class CollisionManager* collsionManager;

	TimerHandle spawnTimer;
	UINT spawnCount;
	SpawnPatten nowPatten;
};

