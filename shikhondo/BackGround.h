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
	ImageDrawInfo Background2;
	ImageDrawInfo Background5;
	ImageDrawInfo Background3;
	ImageDrawInfo Background4;
	ImageDrawInfo LeftSideDownBackground;
	ImageDrawInfo LeftBackground;
	ImageDrawInfo LeftUpBackground;
	ImageDrawInfo RightBackground;
	ImageDrawInfo RightSideDownBackground;
	ImageDrawInfo RightUpBackground;

};

