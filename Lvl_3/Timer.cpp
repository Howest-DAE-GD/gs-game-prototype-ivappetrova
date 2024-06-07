#include "pch.h"
#include "Timer.h"
#include "iostream"
#include <ctime>

Timer::Timer() :
	m_SecondsInTotal{ 12.f },
	m_TotalTimeElapsed{}
{

}
Timer::~Timer()
{

}

void Timer::Print()
{
	int remainingSeconds = std::max(0, int(m_SecondsInTotal - m_TotalTimeElapsed)); // Ensure remainingSeconds is non-negative
	int smallSeconds{ remainingSeconds % 10 };
	int seconds{ (remainingSeconds / 10) % 6 }; // Ensure seconds are in the range 0-5
	int minutes{ remainingSeconds / 60 };

	std::cout << minutes << ":" << seconds << smallSeconds << std::endl;
}

void Timer::Update(float elapsedSec)
{
	m_TotalTimeElapsed += elapsedSec;
}

bool Timer::TimeOut(float elapsedSec)
{
	if ((m_SecondsInTotal - m_TotalTimeElapsed) <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void Timer::Restart()
{
	m_TotalTimeElapsed = 0.0f;
}