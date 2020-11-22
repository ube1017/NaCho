#pragma once
#include "BaseUI.h"
class UI : public BaseUI
{
	virtual HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();				// �޸� ����
	virtual void Update();				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	bool GetIsFullOpen() { return isFullOpen; }
private:
	FPOINT leftBack2pos;
	FPOINT leftBack1pos;
	ImageDrawInfo leftBack1;
	ImageDrawInfo leftBack2;
	ImageDrawInfo LeftSideDownBackground;
	ImageDrawInfo LeftBackground;
	ImageDrawInfo LeftUpBackground;
	ImageDrawInfo RightBackground;
	ImageDrawInfo RightSideDownBackground;
	ImageDrawInfo RightUpBackground;

	int playerHp;
	int playerSoulGauge;
	int playerBoom;
	bool isFullOpen;
	ImageDrawInfo Soulgeiji2;
	ImageDrawInfo SkillGeiji[4];
	ImageDrawInfo Life;
	ImageDrawInfo test;
	ImageDrawInfo SoulGeijiBack;
	ImageDrawInfo SideSoul;
	ImageDrawInfo boss_Hp_Bar1;
	ImageDrawInfo boss_Hp_Bar2;
	ImageDrawInfo boss_Hp_Bar3;
	ImageDrawInfo Font1[14];
	ImageDrawInfo Font2[14];
	ImageDrawInfo Font3[14];
	ImageDrawInfo Bar1;
	ImageDrawInfo Bar2;
	ImageDrawInfo Bar3;


	

};

