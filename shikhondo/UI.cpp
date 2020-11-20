#include "UI.h"

HRESULT UI::Init()
{
	leftBack1pos.x = Play_LeftX + 224;
	leftBack1pos.y = 0;
	leftBack1.drwrc = { (LONG)Play_LeftX, (LONG)-10, (LONG)PlayXSize / 2 , WINSIZE_Y+20};
	leftBack1.imageName = "leftBack";
	leftBack2pos.x = Play_RightX - 224;
	leftBack2pos.y = 0;
	leftBack2.imageName = "leftBack";
	leftBack2.drwrc = { (LONG)PlayXSize / 2  , (LONG)-10 , (LONG)Play_RightX , WINSIZE_Y + 20 };
	LeftUpBackground.imageName = "LeftUpBackground";
	LeftUpBackground.drwrc = { (LONG)0 , (LONG)0 , (LONG)650 , 350 };
	LeftBackground.imageName = "LeftBackground";
	LeftBackground.drwrc = { (LONG)0 , (LONG)150 , (LONG)600 , 700 };
	LeftSideDownBackground.imageName = "LeftSideDownBackground";
	LeftSideDownBackground.drwrc = { (LONG)0 , (LONG)400 , (LONG)430 , WINSIZE_Y };
	RightUpBackground.imageName = "RightUpBackground";
	RightUpBackground.drwrc = { (LONG)600 , (LONG)0 , (LONG)WINSIZE_X , 400 };
	RightBackground.imageName = "RightBackground";
	RightBackground.drwrc = { (LONG)650 , (LONG)150 , (LONG)WINSIZE_X , 700 };
	RightSideDownBackground.imageName = "RightSideDownBackground";
	RightSideDownBackground.drwrc = { (LONG)850 , (LONG)400 , (LONG)WINSIZE_X , WINSIZE_Y };
	return E_NOTIMPL;
}

void UI::Release()
{

}

void UI::Update()
{
	return;
	if (leftBack1pos.x > Play_LeftX - 225)
	{
		leftBack1pos.x--;
		leftBack1.MovePos(MovePosType::X_AIS, -1);
	}
	if (leftBack2pos.x < Play_RightX)
	{
		leftBack2pos.x++;
		leftBack2.MovePos(MovePosType::X_AIS, 1);
	}
}

void UI::Render(HDC hdc)
{
	BaseUI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->DrawAnimImage(hdc, leftBack1);
	//imageManager->DrawAnimImage(hdc, leftBack2);
	imageManager->DrawAnimImage(hdc, LeftBackground);
	imageManager->DrawAnimImage(hdc, LeftSideDownBackground);
	imageManager->DrawAnimImage(hdc, LeftUpBackground);
	imageManager->DrawAnimImage(hdc, RightBackground);
	imageManager->DrawAnimImage(hdc, RightSideDownBackground);
	imageManager->DrawAnimImage(hdc, RightUpBackground);
}
