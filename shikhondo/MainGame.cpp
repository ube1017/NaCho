#include "MainGame.h"
#include "Enemy.h"
#include "Missile.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Player.h"
#include "BackGround.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "EnemyBoss.h"
#include "EnemyManager.h"

#include <ctime>


HRESULT MainGame::Init()
{
	srand((UINT)time(NULL));
	KeyManager::GetSingleton()->Init();
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->Init();

	imageManager->_LoadBitmap("BackBuffer", "mapImage", {1024, 768});
	imageManager->_LoadBitmap("leftBack", "leftBack", { 448, 512 }, { 2, 1 });
	imageManager->_LoadBitmap("leftCloud", "leftCloud", { 1024 , 512 });
	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	MemDC = backBuffer->GetMemDC();
	backbufferInfo.drwrc = { 0,0,WINSIZE_X,WINSIZE_Y };
	backbufferInfo.imageName = "BackBuffer";


	player = CreateObject<Player>();
	backGround = CreateObject<BackGround>();
	Enemy* a = CreateObject<EnemyBoss>();
	EnemyManager* sasdf =  CreateObject<EnemyManager>();
	sasdf->SetMainGame(this);
	sasdf->SpwanEeney<Enemy1>();

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
	backBuffer->Release();
	delete backBuffer;
}

void MainGame::Update()
{
	GameNode::Update();
}

void MainGame::Render()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	
	// ¹é¹öÆÛ
	imageManager->DrawImage(MemDC, backbufferInfo);


	GameNode::Render(MemDC);
	HDC hdc = GetDC(g_hWnd);
	BitBlt(hdc,0,0,WINSIZE_X,WINSIZE_Y , MemDC, 0,0, SRCCOPY);
	DeleteDC(hdc);
}

bool MainGame::CheckCollision(Missile * m1, Missile * m2)
{
	
	return false;
}

float MainGame::GetDistance(FPOINT pos1, FPOINT pos2)
{
	float dist = sqrtf((pos2.x - pos1.x) * (pos2.x - pos1.x)
		+ (pos2.y - pos1.y) * (pos2.y - pos1.y));

	return dist;
}

float MainGame::GetAngle(FPOINT pos1, FPOINT pos2)
{
	float x = pos2.x - pos1.x;
	float y = pos2.y - pos1.y;

	float angle = atan2f(-y, x);

	return angle;
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}
