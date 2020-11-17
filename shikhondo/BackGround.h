#pragma once
#include "UI.h"
class BackGround :public UI
{
public:
	HRESULT Init()			override;				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release()			override;				// �޸� ����
	void Update()			override;				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc)	override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

private:
	FPOINT leftBack2pos;
	FPOINT leftBack1pos;

	ImageDrawInfo leftBack1;
	ImageDrawInfo leftBack2;
};

