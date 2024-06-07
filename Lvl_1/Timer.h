#pragma once

class Timer
{
public:
	Timer();
	~Timer();
	void Print();
	void Update(float elapsedSec);
	void Restart();
	bool TimeOut(float elapsedSec);

private:
	float m_SecondsInTotal;
	float m_TotalTimeElapsed;
};

