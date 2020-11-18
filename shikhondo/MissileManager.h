#pragma once
#include "pch.h"
#include "GameNode.h"


class MissileManager : public GameNode
{

public:
	HRESULT Init();
	void Release();
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	//�̻��� ����
	class Missile* CreateMissile(FPOINT pos = { -100.0f,-100.0f });
	// ������ �̻����� ������ ���°�
	class Missile* SpawnMissile(class Character* onwer, string imageName, FPOINT pos, SIZE size);
	// �÷��̾ �̻��� �����ϴ� �Լ�
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

