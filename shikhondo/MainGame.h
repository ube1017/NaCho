#pragma once

/*
	���漱��, ��ó���� #include

	1. is a ���� : �ҳ�Ÿ�� ����.					-> #include
	2. has a ���� : �ҳ�Ÿ�� ������ ������ �ִ�.	-> ���漱��
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
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render();				// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void MainLoop();
	class UI* GetUI() { return this->ui; }

	bool CheckCollision(Missile* m1, Missile* m2);	// �̻��ϳ��� �浹Ȯ��
	float GetDistance(FPOINT pos1, FPOINT pos2);
	float GetAngle(FPOINT pos1, FPOINT pos2);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

