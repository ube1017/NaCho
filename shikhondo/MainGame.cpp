#include "MainGame.h"
#include "Enemy.h"
#include "Missile.h"
#include "ImageManager.h"
#include "Image.h"
#include "EnemyManager.h"

#include <ctime>


HRESULT MainGame::Init()
{
	srand((UINT)time(NULL));
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->Init();

	imageManager->AddImage("BackBuffer","Image/mapImage.bmp",1024,768);
	Image* backBuffer = imageManager->FindImage("BackBuffer");
	Memdc = backBuffer->GetMemDC();

	return S_OK;
}

void MainGame::Release()
{
	ImageManager::GetSingleton()->Release();
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	Image* backBuffer =	imageManager->FindImage("BackBuffer");
	if (backBuffer)
		backBuffer->Render(Memdc,0,0);

	Rectangle(Memdc,0,0,100,100);

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
