#pragma once
#include "pch.h"
#include "GameNode.h"


class MissileManager : public GameNode
{

public:
	HRESULT Init();
	void Release();
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	//미사일 생성
	class Missile* CreateMissile(FPOINT pos = { -100.0f,-100.0f });
	// 생성된 미사일을 가져다 쓰는거
	class Missile* SpwanMissile(class Character* onwer,FPOINT pos = { 0.0f,0.0f });


private:
	list<Missile*> missileList;
};

