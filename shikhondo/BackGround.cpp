#include "BackGround.h"
#include "Image.h"

HRESULT BackGround::Init()
{
	Background1.imageName = "Background1";
	Background1.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };

	Background2.imageName = "Background2";
	Background2.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background2Time = 0.0f;
	Background2PosY = 0;

	Background5.imageName = "Background5";
	Background5.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background5Time = 0.0f;
	Background5PosY = 0;

	Background3.imageName = "Background3";
	Background3.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background3Time = 0.0f;
	Background3PosY = 0;

	Background4.imageName = "Background4";
	Background4.drwrc = { (LONG)Play_LeftX , (LONG)-1300 , (LONG)Play_RightX , WINSIZE_Y-1300 };
	Background4Time = 0.0f;
	Background4PosY = 0;

	mapImage.imageName = "mapImage";
	mapImage.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };



	return E_NOTIMPL;
}

void BackGround::Release()
{
	BaseUI::Release();
}

void BackGround::Update()
{

	Background3Time += TimerManager::GetSingleton()->GettimeElapsed();
	if (Background3Time >= 0.03f)//앞배경
	{
		Background3PosY += 2;
		Background4PosY += 2;
		Background2PosY ++;
		Background5PosY ++;
		if (Background3PosY <= 1300)
		{
			Background3.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background3PosY - 200, (LONG)Play_RightX + 200,
				WINSIZE_Y + Background3PosY + 200 };
		}
		else 
		{
			Background3PosY = -1300;
		}
		if (Background4PosY <= 2600)
		{
			Background4.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background4PosY - 200 - 1300,
				(LONG)Play_RightX + 200 ,WINSIZE_Y + Background4PosY + 200 - 1300 };
		}
		else
		{
			Background4PosY = 0;
		}
		if (Background2PosY < 1300)
		{
			Background2.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background2PosY - 200,
				(LONG)Play_RightX + 200 ,WINSIZE_Y + Background2PosY + 200 };
		}
		else
		{
			Background2PosY = -1300;
		}
		if (Background5PosY < 2600)
		{
			Background5.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background5PosY - 200 - 1300,
				(LONG)Play_RightX + 200 ,WINSIZE_Y + Background5PosY + 200 - 1300 };
		}
		else
		{
			Background5PosY = 0;
		}
		Background3Time = 0.0f;
	}
	
	//Background2Time += TimerManager::GetSingleton()->GettimeElapsed();
	//if (Background2Time >= 0.05f)//앞배경
	//{
	//	Background2PosY += 3;
	//	if (Background2PosY < 1300)
	//	{
	//		Background2.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background2PosY - 200, (LONG)Play_RightX + 200 ,WINSIZE_Y + Background2PosY + 200 };
	//		Background2Time = 0.0f;
	//	}
	//	else
	//	{
	//		Background2PosY = -1300;
	//	}
	//	Background3Time = 0.0f;
	//}
	//Background5Time += TimerManager::GetSingleton()->GettimeElapsed();
	//if (Background5Time >= 0.05f)//앞배경
	//{
	//	Background5PosY += 3;
	//	if (Background5PosY < 2600)
	//	{
	//		Background5.drwrc = { (LONG)Play_LeftX - 200 , (LONG)Background5PosY - 200 - 1300, (LONG)Play_RightX + 200 ,WINSIZE_Y + Background5PosY + 200 - 1300 };
	//		Background5Time = 0.0f;
	//	}
	//	else
	//	{
	//		Background5PosY = 0;
	//	}
	//	Background5Time = 0.0f;
	//}
}

void BackGround::Render(HDC hdc)
{
	//return;
	BaseUI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->DrawAnimImage(hdc, Background2);
	imageManager->DrawAnimImage(hdc, Background5);
	imageManager->DrawAnimImage(hdc, Background3);
	imageManager->DrawAnimImage(hdc, Background4);
	//imageManager->DrawAnimImage(hdc, Background1);
	//imageManager->DrawAnimImage(hdc, mapImage);

	//  //좌우문오프닝
	//




	//imageManager->DrawAnimImage(hdc, Soulgeiji);
	//imageManager->DrawAnimImage(hdc, SkillGeiji);



	//imageManager->DrawAnimImage(hdc, Background2);   
	//imageManager->DrawAnimImage(hdc, Background4);

	//Rectangle(hdc, Play_LeftX, 0, Play_RightX, WINSIZE_Y);
	//leftCloud
	//leftBack->FrameRender(hdc, leftBack1pos.x, leftBack1pos.y,224, WINSIZE_Y ,0,0);
	//leftBack->FrameRender(hdc, leftBack2pos.x, leftBack2pos.y, 224, WINSIZE_Y , 1, 0);
	//Image* image = ImageManager::GetSingleton()->FindImage("leftCloud");
	//image->Render(hdc,0,0);
}
