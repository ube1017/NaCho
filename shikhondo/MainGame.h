#pragma once

/*
	전방선언, 전처리문 #include

	1. is a 관계 : 소나타는 차다.					-> #include
	2. has a 관계 : 소나타는 바퀴를 가지고 있다.	-> 전방선언
*/
#include "GameNode.h"

class Missile;
class Image;
class MainGame : public GameNode
{
private:
	HDC MemDC;

	Image* backBuffer;
	ImageDrawInfo backbufferInfo;
	//Image* backGround;

	class Scene* scene;
	class UI* ui;
public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render();				// 프레임 단위 출력 (이미지, 텍스트 등)

	void MainLoop();
	class UI* GetUI() { return this->ui; }

	bool CheckCollision(Missile* m1, Missile* m2);	// 미사일끼리 충돌확인
	float GetDistance(FPOINT pos1, FPOINT pos2);
	float GetAngle(FPOINT pos1, FPOINT pos2);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

