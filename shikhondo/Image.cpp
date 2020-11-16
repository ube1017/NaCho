#include "Image.h"



HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	if (imageInfo->hBlendBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hBlendBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	ReleaseDC(g_hWnd, hdc);

	this->isTrans = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	if (imageInfo->hBlendBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	blendFunc.AlphaFormat = 0;	// AC_SRC_ALPHA;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hBlendBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->hOldBlendBit =
		(HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	// �ִϸ��̼� ����
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = imageInfo->width / maxFrameX;
	imageInfo->frameHeight = imageInfo->height / maxFrameY;

	ReleaseDC(g_hWnd, hdc);

	this->isTrans = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}
	if (imageInfo->hBlendBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);
		SelectObject(imageInfo->hBlendDC, imageInfo->hOldBlendBit);
		DeleteObject(imageInfo->hBlendBitmap);
		DeleteDC(imageInfo->hBlendDC);

		delete imageInfo;
		imageInfo = nullptr;
	}

}

void Image::Render(HDC hdc, int destX, int destY)
{
	//imageInfo->x = destX - (imageInfo->width / 2);
	//imageInfo->y = destY - (imageInfo->height / 2);

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ���� ũ��
			imageInfo->height,	// �������� ����� ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY				// ���� �ɼ�
		);
	}

}


void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	imageInfo->currFrameX = currFrameX;
	imageInfo->currFrameY = currFrameY;

	imageInfo->x = static_cast<int>(destX - (imageInfo->frameWidth / 2));
	imageInfo->y = static_cast<int>(destY - (imageInfo->frameHeight / 2));

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			static_cast<int>(imageInfo->x), static_cast<int>(imageInfo->y),
			imageInfo->frameWidth, imageInfo->frameHeight,

			imageInfo->hMemDC,
			imageInfo->currFrameX* imageInfo->frameWidth,
			imageInfo->currFrameY* imageInfo->frameHeight,
			imageInfo->frameWidth, imageInfo->frameHeight,
			transColor);
	}
	else
	{
		BitBlt(
			hdc,				// ���� ������ DC
			imageInfo->x, imageInfo->y,		// ���� ���� ��ġ
			imageInfo->frameWidth,	// �������� ����� ���� ũ��
			imageInfo->frameHeight,	// �������� ����� ���� ũ��

			imageInfo->hMemDC,	// ���� DC
			imageInfo->currFrameX * imageInfo->frameWidth,
			imageInfo->currFrameY * imageInfo->frameHeight,
			SRCCOPY				// ���� �ɼ�
		);
	}
}


void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		//���� �۾� : blendDC,blendBitmap�� �غ�
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc, destX, destY, SRCCOPY);
		// 1. ������ DC�� �׷��� �ִ� ������ blendDC�� ����
		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor);
		// 2. blendDC�� ������ ������ DC�� ���� ���� �Լ��� ����
		AlphaBlend(hdc, destX, destY, imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

Image::Image()
{
}


Image::~Image()
{
}
