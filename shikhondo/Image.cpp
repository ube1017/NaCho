#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	//imageInfo
	HDC hdc = GetDC(g_hWnd);
	
	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::EMPTY);

	blendDC = CreateCompatibleDC(hdc);
	blendBit = CreateCompatibleBitmap(hdc, width, height);
	blendoldBit = (HBITMAP)SelectObject(blendDC, blendBit);
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		this->Release();
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Image::Init(const char* name, int width, int height, int maxFramx, int maxFramy, bool isTrans, COLORREF transColor)
{
	this->Init(name, width, height, isTrans, transColor);
	if (imageInfo)
	{
		imageInfo->maxFramx = maxFramx;
		imageInfo->maxFramy = maxFramy;
		imageInfo->animSizex.cx = width / maxFramx;
		imageInfo->animSizex.cy = height / maxFramy;
	}
	return S_OK;
}

HRESULT Image::Init(const char * name, int width, int height, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, name, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = Cast<BYTE>(IMAGE_LOAD_KIND::FILE);

	this->isTrans = isTrans;
	this->transColor = transColor;


	blendDC = CreateCompatibleDC(hdc);
	blendBit = CreateCompatibleBitmap(hdc, width, height);
	blendoldBit = (HBITMAP)SelectObject(blendDC, blendBit);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		this->Release();
		return E_FAIL;
	}

	blendFun.AlphaFormat = 0;
	blendFun.BlendFlags = 0;
	blendFun.BlendOp = AC_SRC_OVER;
	blendFun.SourceConstantAlpha = 0;
	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteObject(imageInfo->hMemDC);
		delete imageInfo;
		imageInfo = nullptr;

		SelectObject(blendDC, blendoldBit);
		DeleteObject(blendBit);
		DeleteDC(blendDC);
	}
}

void Image::Render(HDC hdc)
{
	if (imageInfo)
	BitBlt(	hdc,												// 복사할 DC
			0, 0,												// 복사할 위치 
			imageInfo->width, imageInfo->height ,		// 원본에서 복사될 가로 크기 , 세로 크기
			imageInfo->hMemDC ,							// 원본의 DC 
			0, 0,												// 원본에서 복사 시작위치
			SRCCOPY);										// 복사 옵션
}

void Image::Render(HDC hdc, int x, int y)
{
	if (imageInfo)
	{
		if (isTrans)
		{
			GdiTransparentBlt(hdc, x, y, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, transColor);
		}
		else
		{
			BitBlt(hdc,												// 복사할 DC
				x, y,												// 복사할 위치 
				imageInfo->width, imageInfo->height,		// 원본에서 복사될 가로 크기 , 세로 크기
				imageInfo->hMemDC,							// 원본의 DC 
				0, 0,												// 원본에서 복사 시작위치
				SRCCOPY);										// 복사 옵션
		}
	}
}

void Image::Render(HDC hdc, int x, int y, int width, int height, POINT cpyStartPos)
{
	if (imageInfo)
	{
		GdiTransparentBlt(	hdc,												
								x, y,												
								width, height,									
								imageInfo->hMemDC,							
								cpyStartPos.x, cpyStartPos.y,
								imageInfo->width, imageInfo->height,	
								transColor);										

	}
}

void Image::AnimRender(HDC hdc, int x, int y, int sizex, int sizey, int framx, int framy)
{
	if (imageInfo)
	{
		if (isTrans)
		{
			int startx = framx *  imageInfo->animSizex.cx;
			int starty = framy *  imageInfo->animSizex.cy;
			GdiTransparentBlt(hdc, x, y, sizex, sizey, imageInfo->hMemDC, startx, starty, imageInfo->animSizex.cx, imageInfo->animSizex.cy, transColor);
		}
	}
}

void Image::AnimRender(HDC hdc, int x, int y, int sizex, int sizey, int animx, int animy,int animSizex, int animSizey)
{
	if (imageInfo)
	{
		if (isTrans)
		{
			GdiTransparentBlt(hdc, x, y, sizex, sizey, imageInfo->hMemDC, animx, animy, animSizex, animSizey, transColor);
		}
		else
		{
			GdiTransparentBlt(	hdc,												
									x, y,												
									sizex, sizey,								
									imageInfo->hMemDC,							
									animx, animy,
									animSizex, animSizey,	
									-1);							
		}
	}
}

void Image::AlphaRender(HDC hdc, int x, int y, int sizex, int sizey, int animx, int animy, int animSizex, int animSizey, BYTE alpha)
{
	blendFun.SourceConstantAlpha = alpha;
	BitBlt(blendDC, 0, 0, sizex, sizey, hdc, x , y , SRCCOPY);
	GdiTransparentBlt(hdc, x, y, sizex, sizey, imageInfo->hMemDC, animx, animy, animSizex, animSizey, transColor);
	AlphaBlend(hdc, x, y, sizex, sizey, blendDC, 0, 0, sizex, sizey, blendFun);
}

void Image::AlphaRender(HDC hdc, int x, int y, int sizex, int sizey, int framx, int framy, BYTE alpha)
{
	blendFun.SourceConstantAlpha = alpha;
	BitBlt(blendDC, 0, 0, sizex, sizey, hdc, x, y, SRCCOPY);
	this->AnimRender(hdc, x, y, sizex, sizey,  framx,framy);
	//GdiTransparentBlt(hdc, x, y, sizex, sizey, imageInfo->hMemDC, animx, animy, animSizex, animSizey, transColor);
	AlphaBlend(hdc, x, y, sizex, sizey, blendDC, 0, 0, sizex, sizey, blendFun);
}
