#include "BackGround.h"
#include "ImageManager.h"
#include "Image.h"

HRESULT BackGround::Init()
{
	leftBack = ImageManager::GetSingleton()->FindImage("leftBack");
	leftBack1pos.x = Play_LeftX + 224;
	leftBack1pos.y = 246;
	leftBack2pos.x = Play_LeftX + 448;
	leftBack2pos.y = 246;
	return E_NOTIMPL;
}

void BackGround::Release()
{
}

void BackGround::Update()
{
	if (leftBack1pos.x > Play_LeftX)
		leftBack1pos.x -= 1;
	if (leftBack2pos.x < Play_LeftX + 672)
		leftBack2pos.x += 1;
}

void BackGround::Render(HDC hdc)
{
	//leftCloud
	leftBack->FrameRender(hdc, leftBack1pos.x, leftBack1pos.y,224, WINSIZE_Y ,0,0);
	leftBack->FrameRender(hdc, leftBack2pos.x, leftBack2pos.y, 224, WINSIZE_Y , 1, 0);
	Image* image = ImageManager::GetSingleton()->FindImage("leftCloud");
	image->Render(hdc,0,0);
}
