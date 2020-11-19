#pragma once
#include "UI.h"
class BackGround :public UI
{
public:
	HRESULT Init()			override;				// 멤버 변수 초기화, 메모리 할당
	void Release()			override;				// 메모리 해제
	void Update()			override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc)	override;		// 프레임 단위 출력 (이미지, 텍스트 등)

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

