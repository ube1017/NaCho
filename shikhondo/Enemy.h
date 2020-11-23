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
	bool GetMapOutCheck() { return mapOutCheck; }
	bool GetMapInCheck() { return mapInCheck; }

	float GetAngle();
	float GetAngle(FPOINT GetPos);

	void OnHit(class Missile* hitMissile) override;

	void SetTargetPOS(FPOINT POS) { this->RandPos = POS; }
	FPOINT GetPos() { return  this->RandPos; }
protected:
	FPOINT RandPos;
	int RandNum;
	int locationCount;
	int missileSpeed;
	float checkTime;
	
	bool AutomaticMissile;
	bool mapInCheck;
	bool mapOutCheck;
};

