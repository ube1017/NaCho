#pragma once
#include "pch.h"
#include "Singleton.h"

class EnemyManager : public Singleton<EnemyManager>
{
private:


public:
	HRESULT Init();
	void Release();
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��
};

