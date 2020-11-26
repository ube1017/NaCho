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
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "UI.h"

#include <ctime>


HRESULT MainGame::Init()
{
	srand((UINT)time(NULL));
	KeyManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->Init();
	imageManager->_LoadBitmap("BackBuffer", "mapImage", { 1024, 768 });

	backBuffer = new Image;
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	MemDC = backBuffer->GetMemDC();
	backbufferInfo.drwrc = { 0,0,WINSIZE_X,WINSIZE_Y };
	backbufferInfo.imageName = "BackBuffer";
	GamePlayStatic::SetMainGame(this);
	ui = CreateObject<UI>();
	ui->SetZOrder(1);

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
	TimerManager::GetSingleton()->Update();
	if (scene)
	{
		if (scene->GetisStart())
			TimerManager::GetSingleton()->TimerUpdate();
	}
}

void MainGame::Render()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	
	// ¹é¹öÆÛ
	imageManager->DrawImage(MemDC, backbufferInfo);

	GameNode::Render(MemDC);
	TimerManager::GetSingleton()->Render(MemDC);
	HDC hdc = GetDC(g_hWnd);
	
	if (scene)
	{
		if (scene->GetIsShake())
		{
			int ShackeX = scene->GetShackeMoveX();
			int ShackeY = scene->GetShackeMoveY();
			int Revision = scene->GetRevision();
			int x = 0;
			int y = 0;
			if (ShackeX != 0)
				x = rand() % ShackeX + Revision;
			if (ShackeY != 0)
				y = rand() % ShackeY + Revision;
			BitBlt(hdc, x, y, WINSIZE_X, WINSIZE_Y, MemDC, 0, 0, SRCCOPY);
		}
		else
			BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, MemDC, 0, 0, SRCCOPY);
	}
	else
		BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, MemDC, 0, 0, SRCCOPY);
	DeleteDC(hdc);
}

void MainGame::MainLoop()
{
	if (scene)
	{
		if (scene->GetisReStart())
		{
			scene->Release();
			scene->SetIsValid(false);
			list<GameNode*>::const_iterator cit = allClass.begin();;
			for (;cit != allClass.end();cit++)
			{
				if (*cit == scene)
				{
					allClass.erase(cit);
					break;
				}
			}
			delete scene;
			
			scene = nullptr;
			TimerManager::GetSingleton()->AllDeleteTimer();
		}
	}
	else
		scene = CreateObject<PlayScene>();
	this->Update();
	this->Render();


	
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
