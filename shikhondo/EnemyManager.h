#pragma once
#include "pch.h"
#include "Singleton.h"

class EnemyManager : public Singleton<EnemyManager>
{
private:


public:
	HRESULT Init();
	void Release();
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등
};

