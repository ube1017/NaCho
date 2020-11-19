#include "BackGround.h"
#include "ImageManager.h"
#include "Image.h"

HRESULT BackGround::Init()
{
	leftBack1pos.x = Play_LeftX + 224;
	leftBack1pos.y = 0;
	leftBack1.drwrc = { (LONG)leftBack1pos.x - 112, (LONG)leftBack1pos.y , (LONG)leftBack1pos.x  + 112 , WINSIZE_Y};
	leftBack1.imageName = "leftBack";
	leftBack2pos.x = Play_RightX - 224;
	leftBack2pos.y = 0;
	leftBack2.imageName = "leftBack";
	leftBack2.drwrc = { (LONG)leftBack2pos.x - 112 , (LONG)leftBack2pos.y , (LONG)leftBack2pos.x + 112 , WINSIZE_Y };
	Background2.imageName = "Background2";
	Background2.drwrc = { (LONG)0 , (LONG)0 , (LONG)512 , 512 };
	Background5.imageName = "Background5";
	Background5.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background3.imageName = "Background3";
	Background3.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background4.imageName = "Background4";
	Background4.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };

	return E_NOTIMPL;
}

void BackGround::Release()
{
	UI::Release();
}

void BackGround::Update()
{
	return;
	if (leftBack1pos.x > Play_LeftX - 225)
	{
		leftBack1pos.x--;
		leftBack1.MovePos(MovePosType::X_AIS, -1);
	}
	if (leftBack2pos.x < Play_RightX )
	{
		leftBack2pos.x++;
		leftBack2.MovePos(MovePosType::X_AIS, 1);
	}
}

void BackGround::Render(HDC hdc)
{
	UI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();

	//imageManager->DrawAnimImage(hdc, leftBack1);    //�¿칮������
	//imageManager->DrawAnimImage(hdc, leftBack2);
	//imageManager->DrawAnimImage(hdc, Background5);
	imageManager->DrawAnimImage(hdc, Background3);
	//imageManager->DrawAnimImage(hdc, Background2);   
	//imageManager->DrawAnimImage(hdc, Background4);

	//Rectangle(hdc, Play_LeftX, 0, Play_RightX, WINSIZE_Y);
	//leftCloud
	//leftBack->FrameRender(hdc, leftBack1pos.x, leftBack1pos.y,224, WINSIZE_Y ,0,0);
	//leftBack->FrameRender(hdc, leftBack2pos.x, leftBack2pos.y, 224, WINSIZE_Y , 1, 0);
	//Image* image = ImageManager::GetSingleton()->FindImage("leftCloud");
	//image->Render(hdc,0,0);
}
