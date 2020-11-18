#pragma once
#include"Scene.h"
class PlayScene : public Scene
{
public:
	//  멤버 변수 초기화, 메모리 할당
	HRESULT Init();
	// 메모리 해제
	void Release();
	// 프레임 단위 게임 로직 실행 ( 데이터 변경)
	void Update();
	// 프레임 단위 출력 (이미지, 텍스트)
	void Render(HDC hdc);

	class Missile* SpawnMissile(class Character* owner,string imageName, FPOINT missilePos, SIZE MissileSize);
private:

	class Player* player;
	class BackGround* backGround;
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
	class CollisionManager* collsionManager;
};

