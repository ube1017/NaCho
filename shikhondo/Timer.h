#pragma once
#include "pch.h"

class Timer
{
private:
	bool isHardware;	// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����
	float timeScale;	// ��� �������� �ʴ� �������� ������ �������� �ð������� ��ȯ
	float timeElapsed;	// ������ �ð��� ���� �ð��� �����
	__int64 currTime;	// ���� �ð� (���� Ÿ�̸� ��)
	__int64 lastTime;	// ���� �ð� (���� Ÿ�̸� ��)
	__int64 periodFrequency;	// ���� Ÿ�̸��� ���ļ� (�ʴ� ������), �������� ������ 0 ��ȯ

	float fpsTimeElapsed;			// ������ ��� �ð� (1��Ȯ��)
	unsigned long fpsFrameCount;	// �ʴ� ������ ��
	unsigned long fps;

public:
	HRESULT Init();
	void Tick();

	unsigned long GetFPS() { return fps; }
	float GetElapsedTime() { return timeElapsed; }
};

