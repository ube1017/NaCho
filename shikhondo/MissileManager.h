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
	class Missile* SpwanMissile(class Character* onwer,FPOINT pos = { 0.0f,0.0f });


private:
	list<Missile*> missileList;
};

