#pragma once
#include "BaseUI.h"
class BackGround :public BaseUI
{
public:
	HRESULT Init()			override;				// 멤버 변수 초기화, 메모리 할당
	void Release()			override;				// 메모리 해제
	void Update()			override;				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc)	override;		// 프레임 단위 출력 (이미지, 텍스트 등)

private:
	
	

	
	ImageDrawInfo Background2;
	ImageDrawInfo Background5;
	ImageDrawInfo Background3;
	ImageDrawInfo Background4;
	ImageDrawInfo Background1;
	ImageDrawInfo mapImage;
	

};

