#pragma once
#include "pch.h"
#include "Singleton.h"

class MissileManager : public Singleton<MissileManager>
{
private:


public:
	HRESULT Init();
	void Release();
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��
};

