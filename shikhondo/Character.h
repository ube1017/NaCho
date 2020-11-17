#pragma once
#include "pch.h"
#include "GameNode.h"



class Character : public GameNode
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	virtual void OnHit(class Missile* hitMissile) {}

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT Getpos() { return pos; }
	const int GetDamge() { return damge; }

	void SetIsDead(bool value) { this->isDead = value; }
	const bool GetIsDead() const { return isDead; }
protected:
	int hp;
	int damge;
	FPOINT pos;
	float speed;
	SIZE size;
	bool isDead;
};

