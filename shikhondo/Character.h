#pragma once
#include "pch.h"
#include "GameNode.h"

class MissileManager;

class Character : public GameNode
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual void OnHit(class Missile* hitMissile) {}

	void SetMissileManager(MissileManager* manager) { this->missileManager = manager; }

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT Getpos() { return pos; }

	SIZE GetSize() { return size; }
	const int GetDamge() { return damge; }

	void SetIsDead(bool value) { this->isDead = value; }
	const bool GetIsDead() const { return isDead; }

	// ĳ���� ����Լ�
	virtual void Death();
protected:
	virtual void Fire() {}
protected:
	int hp;
	int damge;
	FPOINT pos;
	float speed;
	SIZE size;
	bool isDead;
	MissileManager* missileManager;
	// �̹��� �׸��� �ʿ��� ����
	ImageDrawInfo imageinfo;
};

