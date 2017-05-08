#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;
}

float GameTimer::TotalTime() const
{
	if (m_Stopped)
	{
		return (float)(((m_StopTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}

	else
	{
		return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_SecondsPerCount);
	}
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_Stopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_Stopped)
	{
		m_PausedTime += (startTime - m_StopTime);

		m_PrevTime = startTime;

		m_StopTime = 0;
		m_Stopped = false;
	}
}

void GameTimer::Stop()
{
	if (!m_Stopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;
		m_Stopped = true;
	}
}

void GameTimer::Tick()
{
	if (m_Stopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	// 이번 프레임의 시간을 얻는다.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	// 이 시간과 이전 프레임의 시간 차를 구한다.
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;

	// 다음 프레임을 준비한다.
	m_PrevTime = m_CurrTime;

	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}

float GameTimer::DeltaTime() const
{
	return (float)m_DeltaTime;
}


