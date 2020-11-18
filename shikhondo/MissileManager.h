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


	const list<Missile*>* GetMissileList() { return &missileList; }
	const list<Missile*>* GetSpawnMissileList() { return &SpawnMissileList; }
	const list<Missile*>* GetSpawnPlayerMissileList() { return &SpawnPlayerMissileList; }
private:
	list<Missile*> missileList;
	list<Missile*> SpawnMissileList;
	list<Missile*> SpawnPlayerMissileList;
};

