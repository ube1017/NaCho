#pragma once
#include "BaseUI.h"

DELEGATE(PlayerSkillEffect);


enum class DoorState
{
	OPEN = 0,
	BOSSOPEN,
	BOSSCLOSE,
	CLOSE,
	HOLD,
	NONE,
};

class UI : public BaseUI
{
public:
	UI();
	virtual HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	virtual void Release();				// 메모리 해제
	virtual void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetIsStrat(bool value) { this->isStart = value; this->isUsingBackImage = true; }
	bool GetIsStrat() { return this->isStart; }
	void SetBossHp(int* hp) { bossHp = hp; bossMaxHp = *hp;isbossSpawn = true; }
	bool GetIsFullOpen() { return isFullOpen; }
	void AddScore(int value) { this->socre += value; if (maxSocre <= this->socre) maxSocre = this->socre; }


	void SetCloseTimer(float timer = 1.0f);
	void CloseDoor();
	void BossStage();
private:
	void WarningUI();
	void WarningUIEnd();
	void BossFontUI();
	void BossSpawn();
	void WarningAlpha();
	void CloudAlhpa();

	void SkillEffectOn();
	void SkillEffectOff();
public:
	PlayerSkillEffect playerSkillEfect;
private:
	FPOINT leftBack2pos;
	FPOINT leftBack1pos;
	ImageDrawInfo leftBack1;
	ImageDrawInfo leftBack2;	
	ImageDrawInfo UIleftBack1;
	ImageDrawInfo UIleftBack2;
	ImageDrawInfo LeftSideDownBackground;
	ImageDrawInfo LeftBackground;
	ImageDrawInfo LeftUpBackground;
	ImageDrawInfo RightBackground;
	ImageDrawInfo RightSideDownBackground;
	ImageDrawInfo RightUpBackground;
	ImageDrawInfo BossBackground;

	const int* playerHp;
	const int* playerSoulGauge;
	const int* playerBoom;
	const int* bossHp;
	const int* pSoulSocre;
	int socre;
	static int maxSocre;
	int socreCount;
	int soulSocreCount;
	int bossMaxHp;
	int bossFontUIcount;
	// 값이 일정값이상 올라갔다 내려갈때쓰이는 bool 변수
	bool isTurn;

	DoorState closeCount;
	bool isbossSpawn;
	bool isFullOpen;
	bool isWaring;
	bool isbossFont;
	bool isUsingBackImage;
	bool isskillEffect;
	bool isStart;

	TimerHandle warningUIEndtimer;
	TimerHandle bossFontTimer;
	TimerHandle bossSpawnTimer;
	TimerHandle AlphaTimer;
	TimerHandle skillEffectTimer;
	TimerHandle ReStartTimer;

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
	float ImpactTime;
	ImageDrawInfo Impact2;
	float Impact2Time;
	ImageDrawInfo Back;
	ImageDrawInfo BossInit;
	float BossInitTime;
	ImageDrawInfo Warning;
	ImageDrawInfo BossFont[4];
	//ImageDrawInfo BossFont1;
	//ImageDrawInfo BossFont2;
	//ImageDrawInfo BossFont3;
	//ImageDrawInfo BossFont4;
	ImageDrawInfo BossFontBack;
	ImageDrawInfo LeftCloud1;
	ImageDrawInfo LeftCloud2;
	ImageDrawInfo LeftCloud3;
	ImageDrawInfo RightCloud1;
	ImageDrawInfo RightCloud2;
	ImageDrawInfo RightCloud3;
	ImageDrawInfo RightCloud4;
	ImageDrawInfo SoulGeiji3;
	ImageDrawInfo SkillEffect1;
	ImageDrawInfo SkillEffect2;
	ImageDrawInfo SkillEffect3;
	ImageDrawInfo SkillEffect4;
	ImageDrawInfo Bomb;

};

