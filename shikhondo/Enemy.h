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
	virtual bool GetMapOutCheck() { return mapOutCheck; }

	float GetAngle();
	float GetAngle(FPOINT GetPos);

	void OnHit(class Missile* hitMissile) override;

protected:
	FPOINT RandPos;
	int RandNum;
	int locationCount;
	float checkTime;
	bool AutomaticMissile;
	bool mapInCheck;
	bool mapOutCheck;
};

