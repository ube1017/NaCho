#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <wincodec.h>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

#define WINSIZE_X	1280
#define WINSIZE_Y	720
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)
#define ZKey 0x5A
#define XKey 0x58
#define CKey 0x43
// ���� �÷��� ����
#define PlayXSize 650
#define Play_LeftX 315
#define Play_RightX Play_LeftX + PlayXSize
// �̻����� 300������ ������
#define MAX_MISSILE 2000

using namespace std;

extern HWND g_hWnd;
extern HINSTANCE	g_hInstance;


#pragma region typedefs

typedef UINT ZOrder;
#define SUPER(x) typedef x Super;

#pragma endregion



#pragma region CMD ����
//��������� �� CMD â �ѱ�
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#pragma endregion

// ����� �޼���
#ifdef _DEBUG
#define DEBUG_MASSAGE(msg ,... )  printf(msg,##__VA_ARGS__) 
#else
#define DEBUG_MASSAGE(msg ,... )
#endif

// ���̳��� ĳ��Ʈ
template<typename T, typename U>
T* Cast(U* src)
{
	return dynamic_cast<T*>(src);
}

// ��Ÿƽ ĳ��Ʈ
template<typename T, typename U>
T Cast(U src)
{
	return static_cast<T>(src);
}

struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;


enum class Patten
{
	NORMALMOVE,
	HOMINGMOVE,








	MaX,
};



#define MISSILEPATTEN(x) static_cast<int>(x)



#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"