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
	float Background2Time;
	int Background2PosY;
	ImageDrawInfo Background5;
	float Background5Time;
	int Background5PosY;
	ImageDrawInfo Background3[2];
	float Background3Time;
	int Background3PosY;
	ImageDrawInfo Background4;
	float Background4Time;
	int Background4PosY;
	ImageDrawInfo Background1;
	ImageDrawInfo mapImage;
	

};

