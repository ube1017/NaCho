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



protected:
	int hp;
	int damge;
	FPOINT pos;
	float speed;
	SIZE size;

};

