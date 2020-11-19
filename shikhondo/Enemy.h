#pragma once
#include "Character.h"

class Enemy : public Character
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	virtual void RandLocation() {}
	virtual void LocationReset() {}

	float GetAngle();
	float GetAngle(FPOINT GetPos);
protected:
	FPOINT RandPos;
	int RandNum;
	int locationCount;
	float checkTime;
	bool AutomaticMissile;
};

