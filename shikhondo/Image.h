#pragma once
#include "pch.h"

class Image
{
public:
	enum class IMAGE_LOAD_KIND : BYTE
	{
		// 리소스 타입
		RESOURCE,
		// 외부 파일
		FILE,
		// 자제적으로 만든   
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;					// 리소스의 고유한 아이디
		HDC		hMemDC;				// 그리기를 주관하는 핸들 (메모리 관리)
		HBITMAP hBitmap;				// 이미지 정보 
		HBITMAP hOldBit;				// 기존 이미지 정보
		int			width;					// 이미지 가로 크기
		int			height;				// 이미지 세로 크기
		BYTE		loadType;				// 로드 타입
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
	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(int width, int height);
	// 리소스로부터 데이터를 읽어서 비트맵을 만든다.
	HRESULT Init(const DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);
	HRESULT Init(const char* name, int width, int height, int maxFramx,int maxFramy,bool isTrans = FALSE, COLORREF transColor = FALSE);
	// 파일로부터 데이터를 읽어서 비트맵을 만든다.
	HRESULT Init(const char* name, int width, int height, bool isTrans = FALSE, COLORREF transColor = FALSE);


	void Release();

	void Render(HDC hdc);
	void Render(HDC hdc, int x, int y);
	// 이미지 랜더용
	void Render(HDC hdc, int x, int y, int width, int height, POINT cpyStartPos = { 0,0 });
	// 애니메이션 랜더링 x y 좌표 sizexy 이미지 그릴 크기 anim xy 애니미이션 시작 위치 animSizexy 한프레임 애니메이션 크기
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
	bool isTrans;						 // 투명화 여부
	COLORREF transColor;			// 컬러키


	HDC blendDC;
	HBITMAP blendBit;
	HBITMAP blendoldBit;
};

