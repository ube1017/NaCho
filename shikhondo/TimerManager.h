#pragma once
#include "pch.h"
#include "Singleton.h"
class Timer;

struct TimerHandle
{
	bool operator<(const TimerHandle& tm) const
	{
		if (this->timerNum != tm.timerNum)
		{
			if (this->timerNum < tm.timerNum)
				return true;
		}
			return false;
	}

	string timerName;
	UINT timerNum = -1;
};

class TimerManager :public Singleton<TimerManager>
{
	typedef std::map<TimerHandle, Timer*>::const_iterator Const_IteratorTimerMap;


	template<typename UserClass>
	struct Memptr
	{
		typedef typename void(UserClass::* Type)();
	};
public:
	TimerManager();
	~TimerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

public:
	template<typename UserClass>
	void SetTimer(TimerHandle& timerHandle, UserClass* object, typename Memptr<UserClass>::Type fun, float delay = 1.0f)
	{
		map<TimerHandle, Timer*>::iterator it;
		it = timers.find(timerHandle);
		if (it == timers.end())
		{
			if (timerHandle.timerNum == -1)
			{
				Timer* newTimer = new Timer;
				newTimer->Init();
				timerHandle.timerNum = ++timerCount;
				newTimer->SetTimer(object, fun, delay);
				timers.insert(make_pair(timerHandle, newTimer));
			}
			else
			{
				Timer* newTimer = new Timer;
				newTimer->Init();
				newTimer->SetTimer(object, fun, delay);
				timers.insert(make_pair(timerHandle, newTimer));
			}
		}
		else
		{
 			Timer* newTimer = it->second;
			newTimer->timer.UnBind();
			newTimer->SetTimer(object, fun, delay);
		}
	}

	void DeleteTimer(TimerHandle& timerHandle);
private:
	Timer* timer;
	std::map<TimerHandle, Timer*> timers;

	int timerCount;
	char szText[256];
};



#include"Timer.h"