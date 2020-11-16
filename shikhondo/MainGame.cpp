#include "MainGame.h"
#include "Enemy.h"
#include "Missile.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Player.h"
#include "BackGround.h"

#include <ctime>


HRESULT MainGame::Init()
{
	srand((UINT)time(NULL));
	KeyManager::GetSingleton()->Init();
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->Init();

	imageManager->AddImage("BackBuffer","Image/mapImage.bmp",WINSIZE_X, WINSIZE_Y);
	imageManager->AddImage("leftBack", "Image/leftBack.bmp", 448, 512, 2, 1, true, RGB(255, 0, 255));
	imageManager->AddImage("leftCloud", "Image/leftCloud.bmp", 1024/3 * 2, 512/3 * 2, true, RGB(255, 0, 255));
	//leftCloud
	Image* backBuffer = imageManager->FindImage("BackBuffer");
	Memdc = backBuffer->GetMemDC();


	player = new Player;
	player->Init();
	bk = new BackGround;
	bk->Init();

	return S_OK;
}

void MainGame::Release()
{
	ImageManager::GetSingleton()->Release();
	player->Release();
	delete player;
}

void MainGame::Update()
{
	player->Update();
	bk->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	Image* backBuffer =	imageManager->FindImage("BackBuffer");
	if (backBuffer)
		backBuffer->Render(Memdc,0,0);

	Rectangle(Memdc,0,0,100,100);
	bk->Render(Memdc);

	HDC hdc = GetDC(g_hWnd);
	BitBlt(hdc,0,0,WINSIZE_X,WINSIZE_Y , Memdc, 0,0, SRCCOPY);
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
