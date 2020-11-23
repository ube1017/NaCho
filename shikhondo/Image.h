#pragma once
#include "pch.h"

class Image
{
public:
	enum class IMAGE_LOAD_KIND : BYTE
	{
		// ���ҽ� Ÿ��
		RESOURCE,
		// �ܺ� ����
		FILE,
		// ���������� ����   
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;					// ���ҽ��� ������ ���̵�
		HDC		hMemDC;				// �׸��⸦ �ְ��ϴ� �ڵ� (�޸� ����)
		HBITMAP hBitmap;				// �̹��� ���� 
		HBITMAP hOldBit;				// ���� �̹��� ����
		int			width;					// �̹��� ���� ũ��
		int			height;				// �̹��� ���� ũ��
		BYTE		loadType;				// �ε� Ÿ��
		int			maxFramx;
		int			maxFramy;
		SIZE		animSizex;

		tagImageInfo() 
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::EMPTY);
		};
	} IMAGE_INFO, *LPIMAGE_INFO;

public:
	// �� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);
	// ���ҽ��κ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);
	HRESULT Init(const char* name, int width, int height, int maxFramx,int maxFramy,bool isTrans = FALSE, COLORREF transColor = FALSE);
	// ���Ϸκ��� �����͸� �о ��Ʈ���� �����.
	HRESULT Init(const char* name, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);


	void Release();

	void Render(HDC hdc);
	void Render(HDC hdc, int x, int y);
	// �̹��� ������
	void Render(HDC hdc, int x, int y, int width, int height, POINT cpyStartPos = { 0,0 });
	// �ִϸ��̼� ������ x y ��ǥ sizexy �̹��� �׸� ũ�� anim xy �ִϹ��̼� ���� ��ġ animSizexy �������� �ִϸ��̼� ũ��
	void AnimRender(HDC hdc, int x, int y, int sizex, int sizey, int framx, int framy);
	void AnimRender(HDC hdc, int x, int y , int sizex, int sizey , int animx, int animy , int animSizex, int animSizey);
	void AlphaRender(HDC hdc, int x, int y, int sizex, int sizey, int animx, int animy, int animSizex, int animSizey,BYTE alpha);
	void AlphaRender(HDC hdc, int x, int y, int sizex, int sizey, int framx, int framy,BYTE alpha);


	HDC GetMemDC() { return imageInfo->hMemDC; }
	int GetMaxFramX() const { return imageInfo->maxFramx; }
	int GetMaxFramY() const { return imageInfo->maxFramy; }

	BLENDFUNCTION blendFun;
private:
	LPIMAGE_INFO imageInfo;
	char* fileName;
	bool isTrans;						 // ����ȭ ����
	COLORREF transColor;			// �÷�Ű


	HDC blendDC;
	HBITMAP blendBit;
	HBITMAP blendoldBit;
};

