#pragma once
#include "BaseUI.h"
class BackGround :public BaseUI
{
public:
	HRESULT Init()			override;				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release()			override;				// �޸� ����
	void Update()			override;				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc)	override;		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

private:
	
	

	
	ImageDrawInfo Background2;
	ImageDrawInfo Background5;
	ImageDrawInfo Background3;
	ImageDrawInfo Background4;
	ImageDrawInfo Background1;
	ImageDrawInfo mapImage;
	

};

