#pragma once
#include "GameNode.h"
class BaseUI : public GameNode
{
public:
	virtual HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();				// �޸� ����
	virtual void Update();				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

protected:
	FPOINT pos;
	SIZE size;

};

