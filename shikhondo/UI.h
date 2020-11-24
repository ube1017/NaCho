#pragma once
#include "BaseUI.h"
class UI : public BaseUI
{
public:
	virtual HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	virtual void Release();				// 메모리 해제
	virtual void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetBossHp(int* hp) { bossHp = hp; bossMaxHp = *hp;isbossSpawn = true; }
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

	const int* playerHp;
	const int* playerSoulGauge;
	const int* playerBoom;
	const int* bossHp;
	int bossMaxHp;
	bool isbossSpawn;
	bool isFullOpen;

	ImageDrawInfo Soulgeiji2;
	float Soulgeiji2Time;
	ImageDrawInfo SkillGeiji[4];
	float SkillGeijiTime;
	ImageDrawInfo Life[4];
	float LifeTime;
	ImageDrawInfo test;
	ImageDrawInfo SoulGeijiBack;
	ImageDrawInfo SideSoul[2];
	float SideSoulTime;
	ImageDrawInfo boss_Hp_Bar1;
	ImageDrawInfo boss_Hp_Bar2;
	ImageDrawInfo boss_Hp_Bar3;
	ImageDrawInfo Font1[14];
	ImageDrawInfo Font2[14];
	ImageDrawInfo Font3[14];
	ImageDrawInfo Bar1;
	ImageDrawInfo Bar2;
	ImageDrawInfo Bar3;
	ImageDrawInfo Impact;
	ImageDrawInfo Back;

	

};

