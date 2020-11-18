#pragma once
#include "pch.h"
#include "Delegate.h"

DELEGATE(FTimer);

class Timer
{
	template<typename UserClass>
	struct Memptr
	{
		typedef typename void(UserClass::* Type)();
	};
	
public:
	Timer();
	~Timer();

	HRESULT Init();
	void Tick();

	template<typename UserClass>
	void SetTimer(UserClass* object, typename Memptr<UserClass>::Type fun, float delay = 1.0f )
	{
		this->fpsTimeElapsed = 0.0f;
		this->timerDelay = delay;
		this->timer.BindObject(object, fun);
		this->isSetTimer = true;
	}
	void DelteTimer();
	const float GettimeElapsed() { return timeElapsed; }
	const ULONG GetFPSFrameCount() { return fpsFrameCount; }
	const ULONG GetFPS() { return fps; }
private:
	// �ϵ����� ���� Ÿ�̸Ӹ� �����ϴ���
	bool isHardware;
	// ��� �������� �ʴ� �������� ������ �������� �ð������� ��ȯ
	float timeScale;
	// ������ �ð��� ���� �ð��� �����
	float timeElapsed;
	// ���� �ð�(���� Ÿ�̸� ��)
	__int64 currTime;
	// �����ð�(���� Ÿ�̸� ��)
	__int64 lastTime;
	// ���� Ÿ�̸��� ���ļ�(�ʴ� ������), �������� ������ 0 ��ȯ
	__int64 periodFrequency;
	// ������ ��� �ð� (1�� Ȯ��)
	float fpsTimeElapsed;
	// �ʴ� ������ ��
	ULONG fpsFrameCount;
	// �����Ӽ�
	ULONG fps;

	//���� Ÿ�̸Ӱ� ������ �����
	bool isSetTimer;
	//n�ʸ��� ����
	float timerDelay;
public:
	//Ÿ�̸� ��������Ʈ
	FTimer timer;
};

