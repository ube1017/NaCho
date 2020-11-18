#pragma once
#include "pch.h"
#include "GameNode.h"


class MissileManager : public GameNode
{

public:
	HRESULT Init();
	void Release();
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	//미사일 생성
	class Missile* CreateMissile(FPOINT pos = { -100.0f,-100.0f });
	// 생성된 미사일을 가져다 쓰는거
	class Missile* SpawnMissile(class Character* onwer, string imageName, FPOINT pos, SIZE size);
	// 플레이어가 미사일 생성하는 함수
	class Missile* SpawnPlayerMissile(class Character* onwer, string imageName, FPOINT pos, SIZE size);

	void MissileRelease(Character* onwer,Missile* missile);

	const list<Missile*>* GetMissileList() { return &missileList; }
	const list<Missile*>* GetSpawnMissileList() { return &spawnMissileList; }
	const list<Missile*>* GetSpawnPlayerMissileList() { return &spawnPlayerMissileList; }
private:
	list<Missile*> missileList;
	list<Missile*> spawnMissileList;
	list<Missile*> spawnPlayerMissileList;
};

